#include "../../includes/minishell.h"

t_env			*new_elem_env(void)
{
	t_env		*new_elem;

	if (!(new_elem = (t_env *)malloc(sizeof(t_env))))
		ft_error(3);
	new_elem->next = NULL;
	return (new_elem);
}

void				add_elem_env(t_env *env, t_env *new_env)
{
	t_env		*ptr;

	ptr = env;
	if (env == NULL)
		env = new_env;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_env;
	}
}

void				delet_elem_env(t_env *env, t_env *env_unset)
{
	t_env *ptr;

	ptr = env;
	while (ptr->next != env_unset) 
	{ 
	  ptr = ptr->next;
	}
	ptr->next = env_unset->next; // переставляем указатель
	free(env_unset); // освобождаем память удаляемого узла
}

void		write_env_value(t_env *env_export, char *env, int i)
{
	int j;
	int tmp;

	j = 0;
	tmp = i;
	while (env[tmp++])
		j++;
	env_export->content.value = (char *)malloc(sizeof(char) * (j));
	j = 0;
	while (env[i])
		env_export->content.value[j++] = env[i++];
	env_export->content.value[j] = '\0';
}
int		write_env_key(t_env *env_export, char *env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env[i] != '=')
		i++;
	env_export->content.key = (char *)malloc(sizeof(char) * i);
	while (j < i)
	{
		env_export->content.key[j] = env[j];
		j++;
	}
	env_export->content.key[j] = '\0';
	return (j + 1);
}

void		write_env(t_env *env_export, char *env)
{
	int i;

	i = write_env_key(env_export, env);
	write_env_value(env_export, env, i);
}

void			ft_env_sort(t_env *env_export, int i)
{
	t_content		tmp;
	t_env			*ptr;

	ptr = env_export;
	while (i--)
	{
		env_export = ptr;
		while (env_export->next)
		{
			if (ft_strncmp(env_export->content.key, env_export->next->content.key,
				ft_strlen(env_export->content.key) > ft_strlen(env_export->next->content.key) ?
					ft_strlen(env_export->content.key) : ft_strlen(env_export->next->content.key)) > 0)
			{
				tmp = env_export->content;
				env_export->content = env_export->next->content;
				env_export->next->content = tmp;
			}
			env_export = env_export->next;
		}
	}
}

void	ft_print_env(t_env *env_export, int ex)
{
	ft_putstr(env_export->content.key);
	ft_putchar('=');
	if (ex == 1)
		ft_putchar('"');
	ft_putstr(env_export->content.value);
	if (ex == 1)
		ft_putchar('"');
	ft_putchar('\n');
}

void	ft_export_shell(t_env *env_export, char **argv, int argc, int c_env)
{
	t_env *new_env;
	t_env *ptr_env;
	int		args;

	args = 2;
	ptr_env = env_export;
	if (argc < 3)
	{
		ft_env_sort(env_export, c_env);
		while (c_env-- && env_export)
		{
			ft_putstr("declare -x ");
			ft_print_env(env_export, 1);
			env_export = env_export->next;
		}
	}
	else if (argc > 2)
	{
		ptr_env = env_export;
		while (args < argc)
		{
			new_env = new_elem_env();
			write_env(new_env, argv[args]);
			add_elem_env(ptr_env, new_env);
			new_env = new_env->next;
			args++;
		}
		// ft_env_sort(env_export, c_env);
		// while (c_env-- && env_export)
		// {
		// 	ft_putstr("declare -x ");
		// 	ft_print_env(env_export, 1);
		// 	env_export = env_export->next;
		// }
	}
	// else if (argc > 2) // == 3
	// {
	// 	//if "=" true
	// 	// while (args < argv)
	// 	// {

	// 	// }
	// 	// ft_env_sort(env_export, c_env);
	// 	// while (c_env-- && env_export)
	// 	// {
	// 	// 	ft_putstr("declare -x ");
	// 	// 	ft_print_env(env_export, 1);
	// 	// 	env_export = env_export->next;
	// 	// }
	// }
}


t_env 	*ft_create_env(char **env)
{
	t_env	*ptr;
	t_env	*env_export;
	int i;

	ptr = new_elem_env();
	env_export = ptr;
	i = 0;
	while (env[i])
	{
		write_env(ptr, env[i]);
		if (env[i + 1])
		{
			add_elem_env(ptr, new_elem_env());
			ptr = ptr->next;
		}
		i++;
	}
	return (env_export);
}
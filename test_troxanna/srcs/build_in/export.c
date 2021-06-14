#include "../../includes/minishell.h"

t_env			*new_elem_env(void)
{
	t_env		*new_elem;

	if (!(new_elem = (t_env *)malloc(sizeof(t_env))))
		ft_error(NULL, 4);
	if (!(new_elem->content = (t_content *)malloc(sizeof(t_content))))
		ft_error(NULL, 4);
	new_elem->next = NULL;
	//new_elem->content = NULL;
	new_elem->content->value = NULL;
	new_elem->content->key = NULL;
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
	free_t_env(env_unset);
	//free(env_unset); // освобождаем память удаляемого узла
}

void		write_env_value(t_env *env_export, char *env, int i)
{
	int j;
	int tmp;

	j = 0;
	tmp = i;
	while (env[tmp++])
		j++;
	env_export->content->value = (char *)malloc(sizeof(char) * (j));
	j = 0;
	while (env[i])
	{
		(env_export->content)->value[j] = env[i];
		j++;
		i++;
	}
	env_export->content->value[j] = '\0';
}
int		write_env_key(t_env *env_export, char *env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	env_export->content->key = (char *)malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		env_export->content->key[j] = env[j];
		j++;
	}
	env_export->content->key[j] = '\0';
	if (env[i] == '\0')
		return (0);
	return (j + 1);
}

void		write_env(t_env *env_export, char *env)
{
	int i;

	i = write_env_key(env_export, env);
	if (i > 0 && ft_strncmp(env, "OLDPWD", 6))
		write_env_value(env_export, env, i);
}

void			ft_env_sort(t_env *env_export, int i)
{
	t_content		*tmp;
	t_env			*ptr;

	while (i--)
	{
		ptr = env_export;
		while (ptr->next)
		{
			if (ft_strncmp(ptr->content->key, ptr->next->content->key,
				ft_strlen(ptr->content->key) > ft_strlen(ptr->next->content->key) ?
					ft_strlen(ptr->content->key) : ft_strlen(ptr->next->content->key)) > 0)
			{
				tmp = ptr->content;
				ptr->content = ptr->next->content;
				ptr->next->content = tmp;
			}
			ptr = ptr->next;
		}
	}
}

void	ft_print_env(t_env *env_export, int ex)
{
	// if (ex == 1 && !ft_strncmp(env_export->content->key, "OLDPWD", 6))
	// 	return ;
	ft_putstr(env_export->content->key);
	if (env_export->content->value)
	{
		ft_putchar('=');
		if (ex == 1)
			ft_putchar('"');
		ft_putstr(env_export->content->value);
		if (ex == 1)
			ft_putchar('"');
	}
	ft_putchar('\n');
}

void		check_repeat_export(t_env *env_export, char *key)
{
	t_env *ptr;
	int i;

	i = 0;
	while (key[i] != '=' && key[i] != '\0')
		i++;
	ptr = env_export;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content->key, key, i))
		{
			//обработать ситуацию export ll="value" -> export ll
			//в таком случае переменная ll не должна заменяться
			delet_elem_env(env_export, ptr);
			return ;
		}
		ptr = ptr->next;
	}
}

void	ft_export_shell(t_env *env_export, char **argv, int argc)
{
	t_env *new_env;
	t_env *ptr_env;
	int		args;

	args = 1;
	ptr_env = env_export;
	if (argc < 2)
	{
		ft_env_sort(ptr_env, ft_counter_lstenv(env_export));
		while (ptr_env)
		{
			ft_putstr("declare -x ");
			ft_print_env(ptr_env, 1);
			ptr_env = ptr_env->next;
		}
	}
	else if (argc > 1)
	{
		ptr_env = env_export;
		while (args < (argc))
		{
			check_repeat_export(ptr_env, argv[args]); //проверить, нет ли в списке такого ключа. если есть - заменить
			//write(1, "test", 4);
			new_env = new_elem_env();
			write_env(new_env, argv[args]);
			add_elem_env(ptr_env, new_env);
			new_env = new_env->next;
			args++;
		}
	}
}


t_env 	*ft_create_env(char **env, t_env *env_export)
{
	t_env	*ptr;
	t_env	*new_env;
	int i;

	//ptr = new_elem_env();
	ptr = env_export;
	i = 0;
	write_env(ptr, env[i]);
	while (env[++i])
	{
		new_env = new_elem_env();
		write_env(new_env, env[i]);
		add_elem_env(ptr, new_env);
		new_env = new_env->next;
	}
	return (env_export);
}
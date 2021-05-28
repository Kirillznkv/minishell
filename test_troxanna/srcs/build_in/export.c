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

void		write_env_value(t_env *env_export, char *env, int i)
{
	int j;
	int tmp;

	j = 0;
	tmp = i;
	while (env[tmp++])
		j++;
	env_export->content.value = (char *)malloc(sizeof(char) * (j + 2));
	j = 0;
	env_export->content.value[j++] = '"';
	while (env[i])
		env_export->content.value[j++] = env[i++];
	env_export->content.value[j++] = '"';
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

void		write_env_export(t_env *env_export, char *env)
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
			if (ft_strcmp(env_export->content.key, env_export->next->content.key) > 0)
			{
				tmp = env_export->content;
				env_export->content = env_export->next->content;
				env_export->next->content = tmp;
			}
			env_export = env_export->next;
		}
	}
}

void	ft_print_env_export(t_env *env_export)
{
	ft_putstr("declare -x ");
	ft_putstr(env_export->content.key);
	ft_putchar('=');
	ft_putstr(env_export->content.value);
	ft_putchar('\n');
}

void	ft_export_add(char **env)
{
	//если есть = - то записываем в env, иначе только в env_export
}


void	ft_export_shell(char **env)
{
	int i;

	i = 0;
	t_env	*env_export;
	t_env	*ptr;

	ptr = new_elem_env();
	env_export = ptr;
	while (env[i])
	{
		write_env_export(ptr, env[i]);
		if (env[i + 1])
		{
			add_elem_env(ptr, new_elem_env());
			ptr = ptr->next;
		}
		i++;
	}
	//добавляем элементы в env_export
	ft_env_sort(env_export, i);
	while (i-- && env_export)
	{
		ft_print_env_export(env_export);
		env_export = env_export->next;
	}
}
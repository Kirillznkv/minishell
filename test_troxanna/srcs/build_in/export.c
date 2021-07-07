#include "../../includes/minishell.h"

t_env			*new_elem_env(void)
{
	t_env		*new_elem;

	if (!(new_elem = (t_env *)malloc(sizeof(t_env))))
		exit(1);
	if (!(new_elem->content = (t_content *)malloc(sizeof(t_content))))
		exit(1);
	new_elem->next = NULL;
	new_elem->content->value = NULL;
	new_elem->content->key = NULL;
	return (new_elem);
}

void				add_elem_env(t_env *env, t_env *new_env, void (*wrt)(t_env *, char *), char *s)
{
	t_env		*ptr;

	wrt(new_env, s);
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
	while (ptr->next && ptr->next != env_unset) 
	{ 
	  ptr = ptr->next;
	}
	//ptr->next = free_t_env(env_unset); 
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
	env_export->content->value = (char *)malloc(sizeof(char) * (j) + 1);
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
	if (i > 0 && ft_strncmp(env, "OLDPWD", check_equals_sign(env) >
				6 ? check_equals_sign(env) : 6)) //обработать добавление OLDPWD
		write_env_value(env_export, env, i);
}

void			ft_env_sort(t_env **env_export, int i)
{
	t_content		*tmp;
	t_env			*ptr;

	while (i--)
	{
		ptr = *env_export;
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

void	ft_print_env(t_env **env_export, int fd)
{
	// if (ex == 1 && !ft_strncmp(env_export->content->key, "OLDPWD", 6))
	// 	return ;
	t_env	*ptr;

	ptr = *env_export;
	ft_env_sort(env_export, ft_counter_lstenv(*env_export));
	while (ptr)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr(ptr->content->key);
		if (ptr->content->value)
		{
			ft_putchar_fd('=', fd);
			ft_putchar_fd('"', fd);
			ft_putstr_fd(ptr->content->value, fd);
			ft_putchar_fd('"', fd);
		}
		ft_putchar_fd('\n', fd);
		ptr = ptr->next;
	}
}

t_env			*check_repeat_export(t_env *env_export, char *key)
{
	t_env *ptr;
	t_env *tmp;
	int i;

	i = check_equals_sign(key);
	ptr = env_export;
	if (!ft_strncmp(ptr->content->key, key, ft_strlen(ptr->content->key) >
				i ? ft_strlen(ptr->next->content->key) : i))
		return (ptr);
	while (ptr->next)
	{
		if (!ft_strncmp(ptr->next->content->key, key, ft_strlen(ptr->next->content->key) >
				i ? ft_strlen(ptr->next->content->key) : i))
			return (ptr->next);
		ptr = ptr->next;
	}
	return (NULL);
}

int		check_valid_identifier(char *id, int fd)
{
	int i;

	i = 0;
	if (id[0] == '=' || ft_isdigit(id[0]))
	{
		write(fd, id, ft_strlen(id));
		write(fd, ": not a valid identifier\n", 25);
		error_code_dollar = 1;
		return (0);
	}
	return (1);
}

void	ft_export_shell(t_env **env_export, char **argv, int argc, int fd)
{
	t_env *tmp;
	t_env *ptr;
	int		args;

	args = 1;
	if (argc < 2)
		ft_print_env(env_export, fd);
	else if (argc > 1)
	{
		while (args < argc)
		{
			ptr = *env_export;
			if (check_valid_identifier(argv[args], fd))
			{
				tmp = check_repeat_export(ptr, argv[args]);
				if (argv[args][check_equals_sign(argv[args])] == '=')
				{
					if (tmp && *env_export == tmp)
						*env_export = delete_head(tmp);
					else if (tmp)
						ptr = delet_elem(tmp, *env_export);
				}
				if (!tmp || argv[args][check_equals_sign(argv[args])] == '=')
					add_elem_env(*env_export, new_elem_env(), write_env, argv[args]);
			}
			args++;
		}
	}
}

t_env 	*ft_create_env(char **env)
{
	t_env	*ptr;
	t_env	*env_export;
	int i;

	env_export = new_elem_env();
	ptr = env_export;
	i = 0;
	write_env(ptr, env[i]);
	while (env[++i])
		add_elem_env(ptr, new_elem_env(), write_env, env[i]);
	return (env_export);
}
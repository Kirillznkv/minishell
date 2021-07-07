#include "../../includes/minishell.h"

void	write_env_value(t_env *env_export, char *env, int i)
{
	int	j;
	int	tmp;

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

int	write_env_key(t_env *env_export, char *env)
{
	int	i;
	int	j;

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

void	write_env(t_env *env_export, char *env)
{
	int	i;

	i = write_env_key(env_export, env);
	if (i > 0 && ft_strncmp(env, "OLDPWD", check_equals_sign(env)
			> 6 ? check_equals_sign(env) : 6))
		write_env_value(env_export, env, i);
}

void	ft_env_sort(t_env **env_export, int i)
{
	t_content	*tmp;
	t_env		*ptr;

	while (i--)
	{
		ptr = *env_export;
		while (ptr->next)
		{
			if (ft_strncmp(ptr->content->key, ptr->next->content->key,
					ft_strlen(ptr->content->key)
					> ft_strlen(ptr->next->content->key)
					? ft_strlen(ptr->content->key)
					: ft_strlen(ptr->next->content->key)) > 0)
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
	t_env	*ptr;

	ptr = *env_export;
	ft_env_sort(env_export, ft_counter_lstenv(*env_export));
	while (ptr)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(ptr->content->key, fd);
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

void	rewrite_repeat_export()
{
	
}

void	ft_export_shell(t_env **env_export, char **argv, int argc, int fd)
{
	t_env	*tmp;
	t_env	*ptr;
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

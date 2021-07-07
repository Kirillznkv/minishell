#include "../../includes/minishell.h"

char		*get_env(t_env *env, char *str)
{
	int 		i;
	char 		*p_str;
	t_env		*ptr;

	//p_str = NULL;
	i = 0;
	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content->key, str, 0))
			return (ptr->content->value);
		ptr = ptr->next;
	}
	return (NULL);
}



static void		show_pwd(char *str, int fd)
{
	int i;

	i = 0;
	while (str[i] != '/' && str[i])
		i++;
	if (str[i] != '\0')
	{
		ft_putstr_fd(str + i, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	ft_pwd_shell(int fd, t_env *env)
{
	char *str;

	str = getcwd(NULL, 0);
	if (str)
		show_pwd(str, fd);
	free(str);
}

// int		env_check_oldpwd(t_env *env_export)
// {
// 	t_env	*ptr;

// 	ptr = env_export;
// 	while (ptr)
// 	{
// 		if (!ft_strncmp(ptr->content->key, str, 0))
// 		ptr = ptr->next;
// 	}
// }

void	ft_env_shell(char **env, int fd, t_env *env_export)
{
	int i;
	char *tmp;
	int op;

	i = -1;
	op = 1;
	tmp = get_env(env_export, "OLDPWD");
	if (!tmp)
		op = 0;
	while (env[++i])
	{
		if (!(!op && !ft_strncmp(env[i], "OLDPWD", check_equals_sign(env[i]) >
				6 ? check_equals_sign(env[i]) : 6)))
		{
			ft_putstr_fd(env[i], fd);
			ft_putchar_fd('\n', 1);
		}
	}
}


void	ft_unset_shell(t_env **env, char **argv, int argc, int fd)
{
	int 	args;
	t_env	*ptr;
	t_env	*tmp;

	ptr = *env;
	args = 1;
	while (args < argc)
	{
		if (check_valid_identifier(argv[args], fd))
		{
			tmp = check_repeat_export(ptr, argv[args]);
			if (tmp && *env == tmp)
				*env = delete_head(tmp);
			else if (tmp)
				ptr = delet_elem(tmp, *env);
		}
		args++;
	}
}

void	ft_exit_shell(int fd, char **argv, int argc)
{
	//too many arguments 
	if (argc > 2)
	{
		write(fd, "exit\n", 5);
		write(1, "too many arguments\n", 19);
		error_code_dollar = 1;
		return ;
	}
	else if (argc == 2)
		error_code_dollar = ft_atoi(argv[1]);
	else
		error_code_dollar = 0;
	write(fd, "exit\n", 5);
	exit(error_code_dollar);
}
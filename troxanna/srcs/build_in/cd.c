#include "../../includes/minishell.h"

static void	rewrite_env_pwd(t_env *env, const char *str, char *pwd)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content->key, str, 0))
		{
			if (ptr->content->value)
				free(ptr->content->value);
			ptr->content->value = ft_strdup(pwd);
		}
		ptr = ptr->next;
	}
}

static int	check_pwd_and_home(t_env *env, const char *str)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content->key, str, 0))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

static char	*check_argv_cd(char *argv, int fd, t_env *env)
{
	char	*tmp;

	tmp = argv;
	if (!argv || !ft_strncmp(argv, "~", 0))
		tmp = getenv("HOME");
	else if (!ft_strncmp(argv, "-", 0))
	{
		tmp = get_env(env, "OLDPWD");
		if (!tmp)
		{
			ft_error(argv, 1, 1, fd);
			return (NULL);
		}
	}
	if (chdir(tmp) > 0)
	{
		ft_error(argv, 2, 1, fd);
		return (NULL);
	}
	return (tmp);
}

void	ft_cd_shell(char **argv, t_env *env, int fd)
{
	char	*new_pwd;
	char	*old_pwd;
	char	*tmp;

	old_pwd = getcwd(NULL, 0);
	tmp = check_argv_cd(argv[1], fd, env);
	if (!tmp)
		return ;
	if (argv[1] && !ft_strncmp(argv[1], "-", 0))
	{
		ft_putstr_fd(tmp, fd);
		ft_putchar_fd('\n', fd);
	}
	rewrite_env_pwd(env, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (check_pwd_and_home(env, "PWD"))
		rewrite_env_pwd(env, "PWD", new_pwd);
	free(new_pwd);
	free(old_pwd);
}

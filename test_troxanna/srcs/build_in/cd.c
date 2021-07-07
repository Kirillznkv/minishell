
#include "../../includes/minishell.h"

static void		rewrite_env_pwd(t_env *env, const char *str, char *pwd)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content->key, str, 0))
		{
			if (ptr->content->value)
				free(ptr->content->value);
			//ptr->content->value = NULL;
			ptr->content->value = ft_strdup(pwd);
			//write(1, ptr->content->value, ft_strlen(ptr->content->value));
		}
		ptr = ptr->next;
	}
}

static int		check_pwd_and_home(t_env *env, const char *str)
{
	t_env		*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content->key, str, 0))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void			ft_cd_shell(char **argv, t_env *env, int fd)
{
	char	*new_pwd;
	char	*old_pwd;
	char	*tmp;

	//если значения не существует, то выдавать что директория не найдена
	old_pwd = getcwd(NULL, 0);
	tmp = argv[1];
	if (!argv[1] || !ft_strncmp(argv[1], "~", 0))
		tmp = getenv("HOME");
	else if (!ft_strncmp(argv[1], "-", 0))
	{
		tmp = get_env(env, "OLDPWD");
		if (!tmp)
		{
			write(fd, argv[0], ft_strlen(argv[0]));
			write(fd, ": OLDPWD not set\n", 17);
			error_code_dollar = 1;
			return ;
		}
	}
	if (chdir(tmp) == -1)
	{
		write(fd, argv[1], ft_strlen(argv[1]));
		write(fd, ": no such file or directory\n", 28);
		return ;
	}
	if (!ft_strncmp(argv[1], "-", 0))
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
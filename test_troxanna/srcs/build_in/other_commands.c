#include "../../includes/minishell.h"

static void	show_pwd(char *str, int fd)
{
	int	i;

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
	char	*str;

	str = getcwd(NULL, 0);
	if (str)
		show_pwd(str, fd);
	free(str);
}

void	ft_env_shell(char **env, int fd, t_env *env_export)
{
	int		i;
	char	*tmp;
	int		op;

	i = -1;
	op = 1;
	tmp = get_env(env_export, "OLDPWD");
	if (!tmp)
		op = 0;
	while (env[++i])
	{
		if (!(!op && !ft_strncmp(env[i], "OLDPWD", check_equals_sign(env[i]) > 6
					? check_equals_sign(env[i]) : 6)))
		{
			ft_putstr_fd(env[i], fd);
			ft_putchar_fd('\n', 1);
		}
	}
}

void	ft_unset_shell(t_env **env, char **argv, int argc, int fd)
{
	int		args;
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

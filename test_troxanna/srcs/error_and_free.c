#include "../includes/minishell.h"

void	free_array(void **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	array = NULL;
}

void	free_t_env(t_env *env_t)
{
	if (env_t->content->key)
		free(env_t->content->key);
	if (env_t->content->value)
		free(env_t->content->value);
	free(env_t->content);
	free(env_t);
}

void	ft_error(char *name, int n, int err_code, int fd)
{
	if (n == 1)
		ft_putstr_fd("OLDPWD not set\n", fd);
	else if (n == 2)
	{
		ft_putstr_fd(name, fd);
		ft_putstr_fd(": No such file or directory\n", fd);
		ft_putchar_fd('\n', fd);
	}
	else if (n == 3)
		ft_putstr_fd("too many arguments\n", fd);
	else if (n == 4)
	{
		ft_putstr_fd(name, fd);
		ft_putstr_fd(": numeric argument required\n", fd);
	}
	g_error_code_dollar = err_code;
	return ;
}

void	ft_error_exec(char *name, int n, int err_code, int fd)
{
	if (n == 1)
	{
		ft_putstr_fd(name, fd);
		ft_putstr_fd(": permission denied\n", fd);
	}
	else if (n == 2)
	{
		ft_putstr_fd("сommand not found: ", fd);
		ft_putstr_fd(name, fd);
		ft_putchar_fd('\n', fd);
	}
	else if (n == 3)
		ft_putstr_fd("failed to fork\n", fd);
	else if (n == 5)
	{
		ft_putstr_fd("no such file or directory: ", fd);
		ft_putstr_fd(name, fd);
		ft_putchar_fd('\n', fd);
	}
	g_error_code_dollar = err_code;
	exit(g_error_code_dollar);
}

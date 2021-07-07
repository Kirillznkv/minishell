#include "../includes/minishell.h"

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
	error_code_dollar = err_code;
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
	error_code_dollar = err_code;
	exit(error_code_dollar);
}

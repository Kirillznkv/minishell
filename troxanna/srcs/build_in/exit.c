#include "../../includes/minishell.h"

static int	check_exit_number(char *argv)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (!ft_isdigit(argv[i]))
			return (0);
	}
	return (1);
}

void	ft_exit_shell(int fd, char **argv, int argc)
{
	if (argc > 2)
	{
		ft_error(NULL, 3, 1, fd);
		return ;
	}
	else if (argc == 2)
	{
		if (!check_exit_number(argv[1]))
			ft_error(argv[1], 4, 255, fd);
		else
			g_error_code_dollar = ft_atoi(argv[1]);
	}
	else
		g_error_code_dollar = 0;
	write(fd, "exit\n", 5);
	exit(g_error_code_dollar);
}

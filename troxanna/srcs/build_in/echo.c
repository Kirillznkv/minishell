#include "../../includes/minishell.h"

static void	print_echo_star(int fd)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
	{
		perror("diropen");
		exit(1);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			ft_putstr_fd(entry->d_name, fd);
			ft_putchar_fd(' ', fd);
		}
		entry = readdir(dir);
	}
	ft_putchar_fd('\n', fd);
	closedir(dir);
}

static int	echo_case_handling(t_env *env, char *argv)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(env->content->key, argv + 1, 0) && env->content->value)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int	echo_home(char **argv, int fd, int i)
{
	char	*home;

	home = getenv("HOME");
	if (!ft_strncmp(argv[i], "~", 0))
		ft_putstr_fd(home, fd);
	else
		ft_putstr_fd(argv[i], fd);
	return (1);
}

static int	echo_cycle_write(int i, char **argv, int fd)
{
	while (argv[i])
	{
		if (argv[i][0] == '~')
		{
			if (!echo_home(argv, fd, i))
				return (0);
		}
		else
			ft_putstr_fd(argv[i], fd);
		if (argv[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	return (1);
}

void	ft_echo_shell(char **argv, int fd, t_env *env)
{
	int	i;

	i = 1;
	if (!argv[i])
		ft_putchar_fd('\n', fd);
	else if (!ft_strncmp(argv[i], "-n", 2))
	{
		if (!echo_cycle_write(++i, argv, fd))
			return ;
	}
	else if (!ft_strncmp(argv[i], "*", 0))
		print_echo_star(fd);
	else
	{
		if (!echo_cycle_write(i, argv, fd))
			return ;
		ft_putchar_fd('\n', fd);
	}
}

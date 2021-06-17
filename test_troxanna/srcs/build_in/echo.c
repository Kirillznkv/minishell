#include "../../includes/minishell.h"

static void		print_echo_star(int fd)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(".");
	if (!dir) {
        perror("diropen");
        exit(1);
    };
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			ft_putstr_fd(entry->d_name, fd);
			ft_putchar_fd(' ', fd);
		}
	}
	ft_putchar_fd('\n', fd);
	closedir(dir);
}

void			ft_echo_shell(char **argv, int fd)
{
	int i;
	i = 1;
	if (!ft_strncmp(argv[i], "-n", 0))
	{
		while (argv[++i])
		{
			ft_putstr_fd(argv[i], fd);
			if (argv[i + 1])
				ft_putchar_fd(' ', fd);
		}
	}
	else if (!ft_strncmp(argv[i], "*", 0))
		print_echo_star(fd);
	else 
	{
		while (argv[i])
		{
			ft_putstr_fd(argv[i++], fd);
			ft_putchar_fd(' ', fd);
		}
		ft_putchar_fd('\n', fd);
	}
}
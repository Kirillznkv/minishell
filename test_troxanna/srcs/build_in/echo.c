#include "../../includes/minishell.h"

static void		print_echo_star(void)
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
			ft_putstr(entry->d_name);
			ft_putchar(' ');
		}
	}
	ft_putchar('\n');
	closedir(dir);

}

void			ft_echo_shell(char **argv)
{
	int i;
	i = 1;
	if (!ft_strncmp(argv[i], "-n", 0))
	{
		while (argv[++i])
		{
			ft_putstr(argv[i]);
			if (argv[i + 1])
				ft_putchar(' ');
		}
	}
	else if (!ft_strncmp(argv[i], "*", 0))
		print_echo_star();
	else 
	{
		while (argv[i])
		{
			ft_putstr(argv[i++]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
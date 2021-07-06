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

static int		echo_case_handling(t_env *env, char *argv)
{
	t_env *ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(env->content->key, argv + 1, 0) && env->content->value)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void			ft_echo_shell(char **argv, int fd, t_env *env)
{
	int i;

	i = 1;

	if (!argv[i])
		ft_putchar_fd('\n', fd);
	else if (!ft_strncmp(argv[i], "-n", 0))
	{
		while (argv[++i])
		{
			if ((argv[i][0] == '$' && echo_case_handling(env, argv[i])) || argv[i][0] != '$')
				ft_putstr_fd(argv[i], fd);
			if (argv[i + 1] && argv[i][0] != '$')
				ft_putchar_fd(' ', fd);
		}
	}
	else if (!ft_strncmp(argv[i], "*", 0))
		print_echo_star(fd);
	else
	{
		while (argv[i])
		{
			if ((argv[i][0] == '$' && echo_case_handling(env, argv[i])) || argv[i][0] != '$')
				ft_putstr_fd(argv[i], fd);
			if (argv[i + 1] && argv[i][0] != '$')
				ft_putchar_fd(' ', fd);
			i++;
		}
		ft_putchar_fd('\n', fd);
	}
}
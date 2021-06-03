#include "../includes/minishell.h"


// char         *find_path(char **env)
// {
//     char *p_str;
//     int i;

//     i = 0;
//     while (env[i])
// 	{
// 		p_str = ft_strnstr(env[i], "PATH", 4);
// 		if (p_str)
// 			return (p_str);
// 		else
// 			i++;
// 	}
//     return (NULL);
// }

char		*add_slach_arg(char *str)
{
	int count;
	int i;
	char *arg;

	i = 0;
	count = ft_strlen(str);
	arg = malloc(count + 2);
	arg[i] = '/';
	while (str[i])
	{
		arg[i + 1] = str[i];
		i++;
	}
	arg[i + 1] = '\0';
	return (arg);
}

void       exec_run(char **argv, char **env)
{
    char    **path;
    char      *s;
	struct stat buff[1];
    char *bin;
    int i;
	char *arg;

	//s = find_path(env);
	s = getenv("PATH");
    path = ft_split(s + 5, ':');
	arg = add_slach_arg(argv[1]);
	i = 0;
    while (path[i])
    {
		bin = NULL;
        bin = ft_strjoin(path[i], arg);
		if ((lstat(bin, buff)) == 0)
			execve(bin, argv + 1, env);
		else
		{
			free(bin);
			i++;
		}
	}
	free(arg);
}
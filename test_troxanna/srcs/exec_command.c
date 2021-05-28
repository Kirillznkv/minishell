#include "../includes/minishell.h"


char         *find_path(char **env)
{
    char *p_str;
    int i;

    i = 0;
    while (env[i])
	{
		p_str = ft_strnstr(env[i], "PATH", 4);
		if (p_str)
			return (p_str);
		else
			i++;
	}
    return (NULL);
}

void       exec_run(char **argv, char **env)
{
    char    **path;
    char      *s;
	struct stat buff[1];
    char *bin;
    int i;
	int tmp;


	s = find_path(env);
    path = ft_split(s + 5, ':');
	//stat
	//printf("%s\n", path[1]);
	i = 0;
    while (path[i])
    {
		bin = NULL;
        bin = ft_strjoin(path[i], "/ls");
		tmp = lstat(bin, buff);
		// if (lstat(bin, buff) == 0)
		// 	execve(bin, argv, env);
		printf("%d\n", tmp);
        // printf("%s\n", bin);
		if (tmp == -1)
			free(bin);
		// else
		i++;
        //i = execve(bin, argv, env);
       // i = -1;
        // if (i == -1)
        // {
        //     free(bin);
        //     count--;
        // }
    }
    // i = execve(bin, argv, env);
    // printf("%d", i);
    //free(path[1]);
    //if ()

}
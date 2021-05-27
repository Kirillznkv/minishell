#include "../includes/minishell.h"

int         find_path(char **env)
{
    char *p_str;
    int i;

    i = 0;
    while (env[i])
	{
		p_str = ft_strnstr(env[i], "PATH", 4);
		if (p_str)
			return (i);
		else
			i++;
	}
    return (0);
}

// void        malloc_bin_exec(char **path, int count)
// {
//     path = malloc(sizeof(char *) * count);
// }

void        fill_in_bin(int tmp, char *bin, char *path)
{
    int i;

    i = 0;
    tmp++;
    while(path[tmp] != ':' && path[tmp] != '\0')
    {
        bin[i++] = path[tmp++];
    }
    bin[i++] = '/';
    bin[i] = '\0';
}

char       **parse_path(char **env, int *count)
{
    int i;
    int j;
    int tmp;
    char **bin;

    i = find_path(env);
    j = 4;
    while (env[i][j] != '\0')
    {
        if (env[i][j] == ':' || env[i][j + 1] == '\0')
            (*count)++;
        j++;
    }
    bin = malloc(sizeof(char *) * (*count));
    j = 4;
    *count = 0;
    tmp = 4;
    while (env[i][j] != '\0')
    {
        if (env[i][j] == ':' || env[i][j + 1] == '\0')
        {
            bin[*count] = malloc(sizeof(char) * (j - tmp + 1));
            fill_in_bin(tmp, bin[*count], env[i]);
            tmp = j;
            (*count)++;
        }
        j++;
    }
    return (bin);
}

void       exec_run(char **argv, char **env)
{
    char    **path;
    char      *bin;
    int count;
    int i;

    count = 0;
    path = parse_path(env, &count);
    count--;
    while (count >= 0)
    {
        bin = ft_strjoin(path[count], "ls");
        printf("%s\n", bin);
        i = execve(bin, argv, env);
       // i = -1;
        if (i == -1)
        {
            free(bin);
            count--;
        }
    }
    // i = execve(bin, argv, env);
    // printf("%d", i);
    //free(path[1]);
    //if ()

}
#include "../includes/minishell.h"


char		*get_env_char(char **env, char *str)
{
	int i;
	char *ptr;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str) > check_equals_sign(env[i])
									? ft_strlen(str) : check_equals_sign(env[i])))
		{
			ptr = env[i];
			return (ptr + (ft_strlen(str) + 1));
		}
	}
	return (NULL);
}


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

void		exec_fork(t_commands *cmd, char **env, char *bin)
{
	int			a;
	int			xar_exec;
	// a = fork();
	// if (a == 0)
	// {
		if (cmd->fd_out != 1)
		{
			close(1);
			dup2(cmd->fd_out, 1);
		}
		if (cmd->fd_in != 0)
		{
			close(0);
			dup2(cmd->fd_in, 0);
		}
		xar_exec = execve(bin, cmd->argv, env);
		//error_code_dollar = xar_exec;
		if (xar_exec == -1)
			ft_error(cmd->argv[0], 1, 126);
	// }
	// else if (a < 0)
	// 	ft_error(cmd->argv[0], 3);
	// wait(&a);
}

static char		*exec_case_handling(char **env, t_commands *cmd)
{
	char		*bin;
	struct stat	buff[1];

	bin = NULL;
	if (!ft_strncmp("./", cmd->argv[0], 0)
			|| !ft_strncmp("../", cmd->argv[0], 0)
			|| !ft_strncmp("/", cmd->argv[0], 0))
	{
		bin = ft_strdup(cmd->argv[0]);
		error_code_dollar = lstat(bin, buff);
		if (error_code_dollar)
			ft_error(cmd->argv[0], 5, 127);
	}
	return (bin);
}

static char		*exec_find_handling(char **env, t_commands *cmd)
{
	struct stat	buff[1];
    char    	**path;
	int 		i;
	char 		*arg;
	char		*bin;
	char		*ptr;
	
	ptr = get_env_char(env, "PATH");
	if (!ptr || !(path = ft_split(ptr, ':')))
		ft_error(cmd->argv[0], 5, 127);
	arg = add_slach_arg(cmd->argv[0]);
	i = -1;
	while (path[++i])
    {
        bin = ft_strjoin(path[i], arg);
		if ((error_code_dollar = lstat(bin, buff)) == 0)
			break ;
		free(bin);
		bin = NULL;
	}
	free_array((void **)path);
	free(arg);
	if (error_code_dollar)
		ft_error(cmd->argv[0], 2, 127);
	return (bin);
}

void       exec_run(t_commands *cmd, char **env)
{
    char *bin;
	char **test;

	bin = NULL;

	if (!(bin = exec_case_handling(env, cmd)))
			bin = exec_find_handling(env, cmd);	
	if (bin && !error_code_dollar)
	{
		exec_fork(cmd, env, bin);
		free(bin);
	}
	// if (error_code_dollar == 126)
	// 	ft_error(cmd->argv[0], 1, error_code_dollar);
	// else if (error_code_dollar)
}

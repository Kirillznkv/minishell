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

	a = fork();
	if (a == 0)
	{
		if (cmd->fd_out != 1)
		{
			close(0);
			dup2(cmd->fd_out, 1);
		}
		xar_exec = execve(bin, cmd->argv, env);
		error_code_dollar = xar_exec;
		if (xar_exec == -1)
			ft_error(cmd->argv[0], 1);
	}
	else if (a < 0)
		ft_error(cmd->argv[0], 3);
	wait(&a);
}

void	pipe_run(t_commands *cmd, char **env)
{
	int		fd[2];
	pid_t	pid;
	int tmp_fd = dup(0);


	if (cmd->pipe)
	{
		pipe(fd);
		pid = fork();
		if (!pid)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			execve(cmd->argv[0], cmd->argv, env);
			close(fd[1]);
		}
		else
		{
			wait(&pid);
			dup2(fd[0], 0);
			close(fd[1]);
			//execve(cmd->next->argv[0], cmd->next->argv, env);
			//dup2(1, fd[1]);
			exec_fork(cmd->next, env, cmd->next->argv[0]);
			dup2(0, 0);
			close(fd[0]);
			dup2(tmp_fd, 0);
			//close(fd[1]);

		}
	}
	else
		exec_fork(cmd, env, cmd->argv[0]);
}

static char		*exec_case_handling(char **env, t_commands *cmd)
{
	char		*bin;

	bin = NULL;
	if (!ft_strncmp("./", cmd->argv[0], 2)
			|| !ft_strncmp("../", cmd->argv[0], 3)
			|| !ft_strncmp("/", cmd->argv[0], 1))
		bin = ft_strdup(cmd->argv[0]);
	return (bin);
}

static char		*exec_find_handling(char **env, t_commands *cmd)
{
	struct stat	buff[1];
    char    	**path;
	int 		i;
	char 		*arg;
	char		*bin;

	if (!(path = ft_split(find_path(env), ':')))
	{
		ft_error(cmd->argv[0], 5);
		//обработать ошибку - либо сделать exit и выйти из дочернего процесса, либо ретерн
	}
	arg = add_slach_arg(cmd->argv[0]);
	i = -1;
	while (path[++i])
    {
		bin = NULL;
        bin = ft_strjoin(path[i], arg);
		if ((lstat(bin, buff)) == 0)
			break ;
		free(bin);
	}
	free_char_array(path);
	free(arg);
	return (bin);
}

void       exec_run(t_commands *cmd, char **env)
{
    char *bin;

	bin = NULL;
	if (!(bin = exec_case_handling(env, cmd)))
		bin = exec_find_handling(env, cmd);
	if (bin)
	{
		exec_fork(cmd, env, bin);
		free(bin);
	}
	else
		ft_error(cmd->argv[0], 2);
}

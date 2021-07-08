#include "../includes/minishell.h"

static int	count_pipe(t_commands *cmd)
{
	t_commands	*ptr;
	int			i;

	i = 0;
	ptr = cmd;
	while (cmd->pipe)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

static void	pipe_child(int **fd, int i, int count)
{
	if (i == 0)
	{
		close(fd[i][0]);
		dup2(fd[i][1], 1);
	}
	else if (i < count)
	{
		close(fd[i - 1][1]);
		dup2(fd[i - 1][0], 0);
		close(fd[i][0]);
		dup2(fd[i][1], 1);
	}
	else
	{
		close(fd[i - 1][1]);
		dup2(fd[i - 1][0], 0);
	}	
}

static int	fork_start(int *pid, int **fd, int i)
{
	*pid = fork();
	if (*pid != 0)
		close(fd[i][1]);
	return (1);
}

static void	wait_fork(pid_t *pid, int i, int **fd)
{
	int			status;

	while (i > -1)
		waitpid(pid[i--], &status, WUNTRACED | WCONTINUED);
	g_error_code_dollar = WEXITSTATUS(status);
	free_array((void **)fd);
}

void	execute_pipe(t_commands *cmd, char ***env, t_env **env_main)
{
	int			pid_i[2];
	int			**fd;
	t_commands	*ptr;
	pid_t		*pid;
	int			i;

	fd = create_pipe_fd(count_pipe(cmd) + 1);
	ptr = cmd;
	pid = (pid_t *)malloc(sizeof(pid_t) * count_pipe(cmd));
	i = -1;
	while (++i < count_pipe(cmd))
		pipe(fd[i]);
	i = -1;
	while (++i < count_pipe(cmd) + 1)
	{
		if (fork_start(&pid[i], fd, i) && !pid[i])
		{
			pipe_child(fd, i, count_pipe(cmd));
			if (parse_command(ptr, env, env_main))
				exit(g_error_code_dollar);
			exec_run(ptr, *env);
		}
		ptr = ptr->next;
	}
	wait_fork(pid, i, fd);
	free(pid);
}

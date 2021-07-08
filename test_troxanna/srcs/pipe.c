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

static int	**create_pipe_fd(int count)
{
	int		**fd;
	int		i;

	i = 0;
	fd = (int **)malloc(sizeof(int *) * count + 1);
	fd[count] = NULL;
	while (i < count)
		fd[i++] = (int *)malloc(sizeof(int) * 2);
	return (fd);
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

int	fork_start(int *pid, int **fd, int i)
{
	*pid = fork();
	if (*pid != 0)
		close(fd[i][1]);
	return (1);
}

void	execute_pipe(t_commands *cmd, char ***env, t_env **env_main)
{
	int			pid_i[2];
	int			**fd;
	t_commands	*ptr;
	int			status;

	fd = create_pipe_fd(count_pipe(cmd) + 1);
	ptr = cmd;
	pid_i[1] = -1;
	while (++pid_i[1] < count_pipe(cmd))
		pipe(fd[pid_i[1]]);
	pid_i[1] = -1;
	while (++pid_i[1] < count_pipe(cmd) + 1)
	{
		if (fork_start(&pid_i[0], fd, pid_i[1]) && !pid_i[0])
		{
			pipe_child(fd, pid_i[1], count_pipe(cmd));
			if (parse_command(ptr, env, env_main))
				exit(g_error_code_dollar);
			exec_run(ptr, *env);
		}
		ptr = ptr->next;
	}
	waitpid(pid_i[0], &status, WUNTRACED | WCONTINUED);
	g_error_code_dollar = WEXITSTATUS(status);
	free_array((void **)fd);
}

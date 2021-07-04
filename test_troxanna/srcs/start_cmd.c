#include "../includes/minishell.h"

//execute_command

int		count_pipe(t_commands *cmd)
{
	t_commands *ptr;
	int			i;

	i = 0;
	ptr = cmd;
	while(cmd->pipe)
	{
		i++;
		cmd=cmd->next;
	}
	return (i);
}

int		parse_command(t_commands *cmd, char ***env, t_env **env_main)
{
	error_code_dollar = 0;
	if (!ft_strncmp(cmd->argv[0], "env", 0)) 
		ft_env_shell(*env, cmd->fd_out);
	else if (!ft_strncmp(cmd->argv[0], "export", 0))
		ft_export_shell(*env_main, cmd->argv, cmd->argc, cmd->fd_out);
	else if (!ft_strncmp(cmd->argv[0], "pwd", 0))
		ft_pwd_shell(cmd->fd_out, *env_main);
	else if (!ft_strncmp(cmd->argv[0], "echo", 0))
		ft_echo_shell(cmd->argv, cmd->fd_out, *env_main);
	else if (!ft_strncmp(cmd->argv[0], "unset", 0))
		ft_unset_shell(*env_main, cmd->argv, cmd->argc);
	else if (!ft_strncmp(cmd->argv[0], "cd", 0))
		ft_cd_shell(cmd->argv[1], *env_main);
	else if (!ft_strncmp(cmd->argv[0], "exit", 0))
		ft_exit_shell();
	else
		return (0);
	return (1);
}

void		execute_command(t_commands *cmd, char ***env, t_env **env_main)
{
	int		status;
	pid_t	pid;

	if (!parse_command(cmd, env, env_main))
	{
		pid = fork();
		if (!pid)
		{
			exec_run(cmd, *env);
			//exit в случае если execve не отработал - чтобы завершить самостоятельно дочерний процесс
			//exit(1);
		}
		else
		{
			waitpid(pid, &status, WUNTRACED | WCONTINUED);
			error_code_dollar = WEXITSTATUS(status);
		}
	}
}


int		**create_pipe_fd(int count)
{
	int **fd;
	int i;

	i = 0;
	fd = (int **)malloc(sizeof(int *) * count + 1);
	fd[count] = NULL;
	while (i < count)
		fd[i++] = (int *)malloc(sizeof(int) * 2);
	return (fd);
}

void		pipe_child(int **fd, int i, int count)
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

void		execute_pipe(t_commands *cmd, char ***env, t_env **env_main)
{
	int			pid;
	int			**fd;
	t_commands	*ptr;
	int			i;
	int			status;

	fd = create_pipe_fd(count_pipe(cmd) + 1);
	ptr = cmd;
	i = -1;
	while (++i < count_pipe(cmd))
		pipe(fd[i]);
	i = -1;
	while (++i < count_pipe(cmd) + 1)
	{
		pid = fork();
		if (pid != 0)
			close(fd[i][1]);
		if (!pid)
		{
			pipe_child(fd, i, count_pipe(cmd));
			if (!parse_command(ptr, env, env_main))
				exec_run(ptr, *env);
			//exit(0);
		}
		else
		{
			waitpid(pid, &status, WUNTRACED | WCONTINUED);
			error_code_dollar = WEXITSTATUS(status);
		}
		ptr = ptr->next;
	}
	free_array((void **)fd);
}


void		start_cmd(t_commands *cmd, char ***env, t_env **env_main)
{
	int		tmp_fd;
	int		i;

	i = -1;
	tmp_fd = dup(0);
	printf("final %p\n", *env_main);
	if (cmd->pipe)
	{
		//execute_pipe(cmd, env, env_main);
	}
	else
		execute_command(cmd, env, env_main);
	printf("final %p\n", *env_main);
	*env = rewrite_env_parse(*env_main, *env, NULL);
	dup2(tmp_fd, 0);
}
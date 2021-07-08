#include "../includes/minishell.h"

int	parse_command(t_commands *cmd, char ***env, t_env **env_main)
{
	if (!ft_strncmp(cmd->argv[0], "env", 0))
		ft_env_shell(*env, cmd->fd_out, *env_main);
	else if (!ft_strncmp(cmd->argv[0], "export", 0))
		ft_export_shell(env_main, cmd->argv, cmd->argc, cmd->fd_out);
	else if (!ft_strncmp(cmd->argv[0], "pwd", 0))
		ft_pwd_shell(cmd->fd_out, *env_main);
	else if (!ft_strncmp(cmd->argv[0], "echo", 0))
		ft_echo_shell(cmd->argv, cmd->fd_out, *env_main);
	else if (!ft_strncmp(cmd->argv[0], "unset", 0))
		ft_unset_shell(env_main, cmd->argv, cmd->argc, cmd->fd_out);
	else if (!ft_strncmp(cmd->argv[0], "cd", 0))
		ft_cd_shell(cmd->argv, *env_main, cmd->fd_out);
	else if (!ft_strncmp(cmd->argv[0], "exit", 0))
		ft_exit_shell(cmd->fd_out, cmd->argv, cmd->argc);
	else
		return (0);
	return (1);
}

static void	execute_command(t_commands *cmd, char ***env, t_env **env_main)
{
	int		status;
	pid_t	pid;

	if (!parse_command(cmd, env, env_main))
	{
		pid = fork();
		if (!pid)
			exec_run(cmd, *env);
		else
		{
			waitpid(pid, &status, WUNTRACED | WCONTINUED);
			g_error_code_dollar = WEXITSTATUS(status);
		}
	}
}

void	start_cmd(t_commands *cmd, char ***env, t_env **env_main)
{
	int		tmp_fd;
	char	**tmp;

	tmp_fd = dup(0);
	g_error_code_dollar = 0;
	if (cmd->pipe)
		execute_pipe(cmd, env, env_main);
	else
		execute_command(cmd, env, env_main);
	if (!ft_strncmp(cmd->name, "export", 0)
		|| !ft_strncmp(cmd->name, "unset", 0))
		*env = rewrite_env_parse(env_main, *env);
	dup2(tmp_fd, 0);
}

#include "../includes/minishell.h"

static char	*add_slach_arg(char *str)
{
	int		count;
	int		i;
	char	*arg;

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

static void	exec_fork(t_commands *cmd, char **env, char *bin)
{
	int		xar_exec;

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
	if (xar_exec == -1)
		ft_error_exec(cmd->argv[0], 1, 126, cmd->fd_out);
}

static char	*exec_case_handling(char **env, t_commands *cmd)
{
	char		*bin;
	struct stat	buff[1];

	bin = NULL;
	if (!ft_strncmp("./", cmd->argv[0], 2)
		|| !ft_strncmp("../", cmd->argv[0], 3)
		|| !ft_strncmp("/", cmd->argv[0], 1))
	{
		bin = ft_strdup(cmd->argv[0]);
		g_error_code_dollar = lstat(bin, buff);
		if (g_error_code_dollar)
			ft_error_exec(cmd->argv[0], 5, 127, cmd->fd_out);
	}
	return (bin);
}

static char	*exec_find_handling(char **env, t_commands *cmd)
{
	struct stat	buff[1];
	char		**path;
	int			i;
	char		*ptr;
	char		*bin;

	ptr = get_env_char(env, "PATH");
	path = ft_split(ptr, ':');
	if (!ptr || !path)
		ft_error_exec(cmd->argv[0], 5, 127, cmd->fd_out);
	ptr = add_slach_arg(cmd->argv[0]);
	i = -1;
	while (path[++i])
	{
		bin = ft_strjoin(path[i], ptr);
		g_error_code_dollar = lstat(bin, buff);
		if (!g_error_code_dollar)
			break ;
		free(bin);
	}
	free_array((void **)path);
	free(ptr);
	if (g_error_code_dollar)
		ft_error_exec(cmd->argv[0], 2, 127, cmd->fd_out);
	return (bin);
}

void	exec_run(t_commands *cmd, char **env)
{
	char	*bin;
	char	**test;

	bin = exec_case_handling(env, cmd);
	if (!bin)
		bin = exec_find_handling(env, cmd);
	if (bin && !g_error_code_dollar)
	{
		exec_fork(cmd, env, bin);
		free(bin);
	}
}

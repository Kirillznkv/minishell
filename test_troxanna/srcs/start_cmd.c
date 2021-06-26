#include "../includes/minishell.h"



void		parse_command(t_commands *cmd, char ***env, t_env *env_main)
{
	//t_env	*env_main;
	t_env	*ptr;
	char	*line;
	char	**tmp;

	//env_main = ft_create_env(env, new_elem_env());
	//printf("%s\n", cmd->argv[1]);
	if (!ft_strncmp(cmd->argv[0], "env", 3)) 
		ft_env_shell(env_main, cmd->fd_out);
	else if (!ft_strncmp(cmd->argv[0], "export", 6))
		ft_export_shell(env_main, cmd->argv, cmd->argc, cmd->fd_out);
	else if (!ft_strncmp(cmd->argv[0], "pwd", 3))
		ft_pwd_shell(cmd->fd_out, *env);
	else if (!ft_strncmp(cmd->argv[0], "echo", 4))
		ft_echo_shell(cmd->argv, cmd->fd_out, env_main);
	else if (!ft_strncmp(cmd->argv[0], "unset", 5))
		ft_unset_shell(env_main, cmd->argv, cmd->argc);
	else if (!ft_strncmp(cmd->argv[0], "cd", 2))
		ft_cd_shell(cmd->argv[1], env_main);
	else if (!ft_strncmp(cmd->argv[0], "exit", 4))
		ft_exit_shell();
	else
		exec_run(cmd, *env);
	free_char_array(*env);
	*env = rewrite_env_parse(env_main);
}
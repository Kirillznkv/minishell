#include "../includes/minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_env	*env_main;
	int		c_env;

	c_env = 0;
	if (argc < 2)
		ft_error(1);
	env_main = ft_create_env(env, &c_env);
	if (!ft_strncmp(argv[1], "env", 3)) 
		ft_env_shell(env_main, c_env);
	else if (!ft_strncmp(argv[1], "export", 6))
		ft_export_shell(env_main, argv, argc, c_env);
	else if (!ft_strncmp(argv[1], "pwd", 3))
		ft_pwd_shell(env);
	else if (!ft_strncmp(argv[1], "echo", 4))
		ft_echo_shell(argv);
	else if (!ft_strncmp(argv[1], "unset", 5))
		ft_unset_shell(env_main, argv, argc, c_env);
	else if (!ft_strncmp(argv[1], "cd", 2))
		ft_cd_shell(env, argv[2]);
	else if (!ft_strncmp(argv[1], "exit", 4))
		ft_exit_shell();
	else
		exec_run(argv, env);
}
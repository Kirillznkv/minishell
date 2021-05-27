#include "../includes/minishell.h"

int		main(int argc, char **argv, char **env)
{
	// if (argc < 2)
	// 	ft_error(1);
	//write(1, "test", 5);
	if (!ft_strcmp(argv[1], "env")) 
		ft_env_shell(env);
	else if (!ft_strcmp(argv[1], "export"))
		ft_export_shell(env);
	else if (!ft_strcmp(argv[1], "pwd"))
		ft_pwd_shell(env);
	else if (!ft_strcmp(argv[1], "echo"))
		ft_echo_shell(argv);
	else if (!ft_strcmp(argv[1], "unset"))
		ft_unset_shell(env, argv, argc - 2);
	else if (!ft_strcmp(argv[1], "cd"))
		ft_cd_shell(env, argv[2]);
	else if (!ft_strcmp(argv[1], "exit"))
		ft_exit_shell();
	else
		exec_run(argv, env);
}
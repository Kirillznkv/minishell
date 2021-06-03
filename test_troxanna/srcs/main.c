#include "../includes/minishell.h"

int		ft_counter_env(char **env)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	return (i);
}

int			ft_counter_lstenv(t_env *lst)
{
	t_env	*beg;
	int		size;

	size = 0;
	beg = lst;
	while (beg)
	{
		beg = beg->next;
		size++;
	}
	return (size);
}

// void	env_parse(t_env *env_main, char **env_parse)
// {
// 	t_env 	*ptr;
// 	char	*tmp;

// 	int		i;

// 	ptr = env_main;
// 	i = 0;
// 	while (ptr)
// 	{
// 		env_parse[i] = ft_strjoin(env_main->content.key, env_main->content.value);
// 		i++;
// 		ptr = ptr->next;
// 	}
// }

//free (env_parse)

int		main(int argc, char **argv, char **env)
{
	t_env	*env_main;
	char	**env_parse;
	int		c_env;

	if (argc < 2)
		ft_error(1);
	env_main = ft_create_env(env);
	c_env = ft_counter_env(env);
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
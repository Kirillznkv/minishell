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
	t_env	*ptr;
	int		size;

	size = 0;
	ptr = lst;
	while (ptr)
	{
		ptr = ptr->next;
		size++;
	}
	return (size);
}


void	free_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

char	**create_env_parse(t_env *env, char **env_parse)
{
	t_env	*ptr;
	char	*tmp;
	int i;

	if (env_parse)
		free_env(env_parse);
	i = ft_counter_lstenv(env);
	env_parse = malloc(sizeof(char *) * i + 1);
	env_parse[i] = NULL;
	ptr = env;
	i = -1;
	while (ptr)
	{
		//проверка на запись в env из env_export только значений со знаком '='
		if (ptr->content.value)
		{
			tmp = ft_strjoin(ptr->content.key, "=");
			env_parse[++i] = ft_strjoin(tmp, ptr->content.value);
			free(tmp);
		}
		ptr = ptr->next;
	}
	return (env_parse);
}


int		main(int argc, char **argv, char **env)
{
	t_env	*env_main;
	char	**env_parse;
	int		c_env;

	env_parse = NULL;
	// if (argc < 2)
	// 	ft_error(1);
	env_main = ft_create_env(env);
	env_parse = create_env_parse(env_main, env_parse);
	c_env = ft_counter_lstenv(env_main);
	//printf("%s\n", env_main->content.key);
	if (!ft_strncmp(argv[1], "env", 3)) 
		ft_env_shell(env_main, c_env);
	else if (!ft_strncmp(argv[1], "export", 6))
		ft_export_shell(env_main, argv, argc, c_env);
	else if (!ft_strncmp(argv[1], "pwd", 3))
		ft_pwd_shell();
	else if (!ft_strncmp(argv[1], "echo", 4))
		ft_echo_shell(argv);
	else if (!ft_strncmp(argv[1], "unset", 5))
		ft_unset_shell(env_main, argv, argc, c_env);
	else if (!ft_strncmp(argv[1], "cd", 2))
		ft_cd_shell(argv[2]);
	else if (!ft_strncmp(argv[1], "exit", 4))
		ft_exit_shell();
	else
		exec_run(argv, env_parse);
}
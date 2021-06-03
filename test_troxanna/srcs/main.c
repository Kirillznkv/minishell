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

char	**create_env(char **env)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
			j++;
		new_env[i] = malloc(sizeof(char) * j + 1);
		j = 0;
		while (env[i][j])
		{
			new_env[i][j] = env[i][j];
			j++;
		}
		new_env[i][j] = '\0';
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

// void			get_key_and_value(char *env, t_env *new_env)
// {
// 	int i;

// 	i = 0;
	
// }

// t_env			*new_elem_env(void)
// {
// 	t_env		*new_elem;

// 	if (!(new_elem = (t_env *)malloc(sizeof(t_env))))
// 		ft_error(3);
// 	new_elem->next = NULL;
// 	return (new_elem);
// }

// void				add_elem_env(t_env *env, t_env *new_env)
// {
// 	t_env		*ptr;

// 	ptr = env;
// 	if (env == NULL)
// 		env = new_env;
// 	else
// 	{
// 		while (ptr->next)
// 			ptr = ptr->next;
// 		ptr->next = new_env;
// 	}
// }

// t_env	*create_env_lst(char **env)
// {
// 	t_env	*ptr;
// 	t_env	*env_export;
// 	int i;

// 	ptr = new_elem_env();
// 	env_export = ptr;
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (env[i + 1])
// 		{
// 			add_elem_env(ptr, new_elem_env());
// 			ptr = ptr->next;
// 		}
// 		i++;
// 	}
// 	return (env_export);
// }

int		main(int argc, char **argv, char **env)
{
	t_env	*env_main;
	char	**env_parse;
	int		c_env;

	if (argc < 2)
		ft_error(1);
	//malloc array char
	env_parse = create_env(env);
	// while (env_parse[i])
	// {
	// 	printf("%s\n", env_parse[i]);
	// 	i++;
	// }
	//malloc list
	env_main = ft_create_env(env_parse);
	c_env = ft_counter_env(env_parse);
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
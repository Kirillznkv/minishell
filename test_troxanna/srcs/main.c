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

void	write_env_line(t_content line, char *new_line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line.key[i])
	{
		new_line[i] = line.key[i];
		i++;
	}
	new_line[i++] = '=';
	while (line.value[j])
	{
		new_line[i] = line.value[j];
		j++;
		i++;
	}
	new_line[i] = '\0';
	//printf("%s\n", new_line);
}

char	**create_env_parse(t_env *env, char **env_parse)
{
	t_env	*ptr;
	int i;
	int j[2];
	int count;

	if (env_parse)
		free_env(env_parse);
	i = ft_counter_lstenv(env);
	env_parse = malloc(sizeof(char *) * i);
	ptr = env;
	while (i > 0 && ptr)
	{
		//проверка на запись в env из env_export только значений со знаком '='
		if (ptr->content.value)
		{
			j[0] = 0;
			j[1] = 0;
			while (ptr->content.key[j[0]])
				j[0]++;
			while (ptr->content.value[j[1]])
				j[1]++;
			//выделяем память под ключ + значение + '=' + '\0'
			count = j[0] + j[1] + 2;
			env_parse[i] = malloc(sizeof(char *) * (j[0] + j[1] + 2));
			write_env_line(ptr->content, env_parse[i]);
		}
		i++;
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
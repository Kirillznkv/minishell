#include "../includes/minishell.h"

char		**malloc_env(char **env)
{
	int 	i;
	int 	j;
	char	**env_malloc;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	env_malloc = (char **)malloc(sizeof(char *) * i);
	if (!env_malloc)
		return (NULL);
	while (env[i])
	{
		while (env[j])
			j++;
		env_malloc[i] = (char *)malloc(sizeof(char) * j + 1);
		i--;
	}
	return (env_malloc);
}	

char		**ft_env_sort(char **env)
{
	int 	c[2];
	char	**env_sorted;


	c[0] = 0;
	c[1] = 0;
	env_sorted = malloc_env(env);
	//Продумать, какой метод сортировки использовать
	// if (ft_isalpha(env[c[0]][c[1]])
	// {
	// 	while (env[c[0]])
	// 	{
	// 		if (env[c[0] + 1] && env[c[0] + 1][c[1]] < env[c[0]][c[1]])

	// 	}
	// }
	return (env_sorted);
}

static char		*get_pwd(char **env)
{
	int 		i;
	char 		*p_str;

	p_str = NULL;
	i = 0;
	while (env[i])
	{
		p_str = ft_strnstr(env[i], "PWD", 3);
		if (p_str)
			return (p_str);
		else
			i++;
	}
	return (NULL);
}

static void		show_pwd(char *str)
{
	int i;

	i = 0;
	while (str[i] != '/' && str[i])
		i++;
	if (str[i] != '\0')
	{
		ft_putstr(str + i);
		ft_putchar('\n');
	}
}

void	ft_echo_shell(char **argv)
{
	int i;

	i = 2;
	while (argv[i])
	{
		ft_putstr(argv[i++]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

void	ft_pwd_shell(char **env)
{
	char *str;

	str = get_pwd(env);
	if (str)
		show_pwd(str);
}

void	ft_export_shell(char **env)
{
	int i;

	i = 0;
	//ft_env_sort(env);
	while (env[i])
	{
		ft_putstr("declare -x ");
		ft_putstr(env[i++]);
		ft_putchar('\n');
	}
}

void	ft_env_shell(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i++]);
		ft_putchar('\n');
	}
}

void	ft_unset_shell(char **env, char **argv, int args)
{
	//1. Получить export (хранить значения export в статической переменной (?))

	char	**key_env;
	int 	i;

	i = 0;
	//2. Получить ключи экспорта (создать экспорт не как массив, а как структуру ключ - значение)
	while (args)
	{
		//if (!ft_strcmp(key_env[i], argv[args])) 
	}
}
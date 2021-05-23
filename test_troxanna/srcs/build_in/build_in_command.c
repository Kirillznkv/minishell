#include "../../includes/minishell.h"

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
	//1. Получить export (хранить значения export в статической переменной (?) - уточнить)

	t_env	*env_unset;
	int 	i;

	i = 0;
	while (args)
	{
		//поиск необходимого элемента списка (ключ == аргумент)
		//удаление элемента из списка, если нашли
		//if (!ft_strcmp(key_env[i], argv[args])) 
	}
}
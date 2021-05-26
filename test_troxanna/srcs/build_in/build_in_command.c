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

void		ft_cd_shell(char **env, char *argv)
{
	char new_pwd[1024];
	int	size = ft_strlen(get_pwd(env));
	char old_pwd[size];

	getcwd(old_pwd, sizeof(old_pwd));
	chdir(argv);
	getcwd(new_pwd, sizeof(new_pwd));
	printf("%s\n", new_pwd);

	// if (new_pwd)
	// {
	// 	if (argv[0] == '.' && argv[1] == '.')
	// 	{
	// 		while (new_pwd[j] != '/')
	// 			j--;
	// 		ft_bzero(new_pwd + j, (size_t)i);
	// 	}
	// 	//добавить old к pwd
	// 	printf ("%s\n", old_pwd);
	// 	show_pwd(env[15]);
	// }
	//free(old_pwd);
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
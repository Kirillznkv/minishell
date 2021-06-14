#include "../../includes/minishell.h"

// static char		*get_pwd(char **env)
// {
// 	int 		i;
// 	char 		*p_str;

// 	p_str = NULL;
// 	i = 0;
// 	while (env[i])
// 	{
// 		p_str = ft_strnstr(env[i], "PWD", 3);
// 		if (p_str)
// 			return (p_str);
// 		else
// 			i++;
// 	}
// 	return (NULL);
// }

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

	i = 1;
	if (!ft_strncmp(argv[i], "-n", 0))
	{
		while (argv[++i])
		{
			ft_putstr(argv[i]);
			if (argv[i + 1])
				ft_putchar(' ');
		}
	}
	else 
	{
		while (argv[i])
		{
			ft_putstr(argv[i++]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}

void	ft_pwd_shell()
{
	char *str;

	str = getenv("PWD");
	if (str)
		show_pwd(str);
}

void	ft_env_shell(t_env *env)
{
	t_env *ptr;

	ptr = env;

	while (ptr)
	{
		if (ptr->content->value)
			ft_print_env(ptr, 0);
		ptr = ptr->next;
	}
}

void		ft_cd_shell(char *argv)
{
	char new_pwd[1024];
	int	size = ft_strlen(getenv("PATH"));
	char old_pwd[size];

	//HOME dir
	getcwd(old_pwd, sizeof(old_pwd));
	chdir(argv);
	getcwd(new_pwd, sizeof(new_pwd));
}

void	split_argv_unset(char *argv, int *i)
{
	while (argv[*i] != '=' && argv[*i] != '\0')
			(*i)++;
}


void	ft_unset_shell(t_env *env, char **argv, int argc)
{
	int 	i;
	int 	args;
	//t_env	*env_unset;
	t_env	*ptr;
	int counter;

	ptr = env;
	//if argc == 3
	while(ptr)
	{
		i = 0;
		args = 1;
		while (args < (argc - 1))
		{
			split_argv_unset(argv[args], &i);
			if((!ft_strncmp(argv[args], ptr->content->key, i)))
				delet_elem_env(env, ptr);
			args++;
		}
		ptr = ptr->next;
	}
	// counter = ft_counter_lstenv(env);
	// ft_env_shell(env, counter + 2);
	// получить удаляемый элемент списка
	// delet_elem_env(env, env_unset);
}

void	ft_exit_shell()
{
	exit(EXIT_SUCCESS);
}
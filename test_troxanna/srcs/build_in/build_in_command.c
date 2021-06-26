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

static void		show_pwd(char *str, int fd)
{
	int i;

	i = 0;
	while (str[i] != '/' && str[i])
		i++;
	if (str[i] != '\0')
	{
		ft_putstr_fd(str + i, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	ft_pwd_shell(int fd, char **env)
{
	char *str;

	str = get_pwd(env);
	if (str)
		show_pwd(str, fd);
}

void	ft_env_shell(t_env *env, int fd)
{
	t_env *ptr;

	ptr = env;

	while (ptr)
	{
		if (ptr->content->value)
			ft_print_env(ptr, 0, fd);
		ptr = ptr->next;
	}
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
		while (args < (argc))
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
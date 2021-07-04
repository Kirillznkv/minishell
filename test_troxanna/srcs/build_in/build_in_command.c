#include "../../includes/minishell.h"

char		*get_env(t_env *env, char *str)
{
	int 		i;
	char 		*p_str;
	t_env		*ptr;

	//p_str = NULL;
	i = 0;
	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content->key, str, 0))
			return (ptr->content->value);
		ptr = ptr->next;
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

void	ft_pwd_shell(int fd, t_env *env)
{
	char *str;

	str = getcwd(NULL, 0);
	if (str)
		show_pwd(str, fd);
	free(str);
}

void	ft_env_shell(char **env, int fd)
{
	int i;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd(env[i], fd);
		ft_putchar_fd('\n', 1);
	}
	// t_env *ptr;

	// ptr = env;

	// while (ptr)
	// {
	// 	if (ptr->content->value)
	// 		ft_print_env(ptr, 0, fd);
	// 	ptr = ptr->next;
	// }
}

void	split_argv_unset(char *argv, int *i)
{
	while (argv[*i] != '=' && argv[*i] != '\0')
			(*i)++;
}


void	ft_unset_shell(t_env **env, char **argv, int argc)
{
	int 	i;
	int 	args;
	//t_env	*env_unset;
	t_env	*ptr;
	int counter;

	ptr = *env;
	args = 1;
	while (args < argc)
	{
		*env = check_repeat_export(ptr, argv[args]); //проверить, нет ли в списке такого ключа. если есть - заменить
		args++;
	}
	//if argc == 3

	// while(ptr->next)
	// {
	// 	i = 0;
	// 	args = 1;
	// 	while (args < (argc))
	// 	{
	// 		split_argv_unset(argv[args], &i);
	// 		if((!ft_strncmp(argv[args], ptr->next->content->key, ft_strlen(argv[args]) >
	// 			i ? ft_strlen(ptr->next->content->key) : i)))
	// 			ptr = delet_elem(ptr->next, *env);
	// 		args++;
	// 	}
	// 	ptr = ptr->next;
	// }

}

void	ft_exit_shell()
{
	exit(error_code_dollar);
}
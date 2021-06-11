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


void	free_char_array(char **env)
{
	int i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

void		ft_putchar(char c)
{
	write(1, &c, sizeof(c));
}

void		ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void		ft_error(char *name, int n)
{
	if (n == 1)
	{
		ft_putstr(name);
		write(1, ": permission denied\n", 20);
	}
	else if (n == 2)
	{
		ft_putstr(name);
		write(1, ": Command not found\n", 21);
	}
	else if (n == 3)
		write(1, "failed to fork\n", 15);
	exit(EXIT_FAILURE);
}

// t_env	*free_t_env(t_env *env_t)
// {
// 	t_env	*env_next;

// 	env_next = env_t->next;
// 	if (env_t->content.key)
// 		free(env_t->content.key);
// 	if (env_t->content.value)
// 		free(env_t->content.value);
// 	//free(env_t);
// 	return (env_next);
// }

char	**rewrite_env_parse(t_env *env, char **env_parse)
{
	t_env	*ptr;
	char	*tmp;
	int i;

	if (env_parse)
		free_char_array(env_parse);
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
		//ptr = free_t_env(ptr);
	}
	return (env_parse);
}
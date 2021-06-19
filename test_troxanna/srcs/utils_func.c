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

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
	env = NULL;
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
		write(1, ": сommand not found\n", 21);
	}
	else if (n == 3)
		write(1, "failed to fork\n", 15);
	else if (n == 4)
		write(1, "mallock error\n", 14);
	else if (n == 5)
	{
		write(1, "no such file or directory: ", 27);
		ft_putstr(name);
		ft_putchar('\n');
	}
	exit(EXIT_FAILURE);
}

t_env	*free_t_env(t_env *env_t)
{
	t_env	*env_next;

	env_next = env_t->next;
	if (env_t->content->key)
		free(env_t->content->key);
	if (env_t->content->value)
		free(env_t->content->value);
	free(env_t->content);
	free(env_t);
	return (env_next);
}

char	**rewrite_env_parse(t_env *env)
{
	t_env	*ptr;
	char	*tmp;
	char 	**env_parse;
	int i;

	ptr = env;
	i = 0;
	while (ptr)
	{
		if (ptr->content->value != NULL)
			i++;
		ptr = ptr->next;
	}
	//printf("%d\n", i);
	//i = ft_counter_lstenv(env);
	env_parse = malloc(sizeof(char *) * i + 1);
	env_parse[i] = NULL;
	ptr = env;
	i = 0;
	while (ptr)
	{
		//проверка на запись в env из env_export только значений со знаком '='
		if (ptr->content->value != NULL)
		{
			tmp = ft_strjoin(ptr->content->key, "=");
			env_parse[i] = ft_strjoin(tmp, ptr->content->value);
			free(tmp);
			//printf("%s\n", env_parse[i]);
			i++;
		}
		ptr = ptr->next;
		//ptr = free_t_env(ptr);
	}
	//printf("%d\n", i);
	return (env_parse);
}

char	**new_env_malloc(char **env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(i * sizeof(char*));
	j = -1;
	while (++j < i)
		new_env[j] = ft_strdup(env[j]);
	return (new_env);
}
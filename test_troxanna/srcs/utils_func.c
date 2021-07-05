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


void	free_array(void **array)
{
	int i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	array = NULL;
}

void		ft_putchar(char c)
{
	write(1, &c, sizeof(c));
}

void		ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void		ft_error(char *name, int n, int err_code)
{
	if (n == 1)
	{
		ft_putstr(name);
		write(1, ": permission denied\n", 20);
		//return ;
	}
	else if (n == 2)
	{
		ft_putstr(name);
		write(1, ": сommand not found\n", 21);
		//return ;
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
		//return ;
	}
	//добавить обработку ошибки
	error_code_dollar = err_code;
	exit(error_code_dollar);
}

t_env		*delete_head(t_env *root)
{
  t_env		*temp;
  temp = root->next;
  free_t_env(root); // освобождение памяти текущего корня
  return(temp); // новый корень списка
}

t_env		*delet_elem(t_env *lst, t_env *root)
{
  t_env *temp;
  temp = root;
  while (temp->next != lst) // просматриваем список начиная с корня
  { // пока не найдем узел, предшествующий lst
    temp = temp->next;
  }
  temp->next = lst->next; // переставляем указатель
  free_t_env(lst); // освобождаем память удаляемого узла
  return(temp);
}

void		free_t_env(t_env *env_t)
{
	//t_env	*env_next;
//
	//env_next = env_t->next;
	if (env_t->content->key)
		free(env_t->content->key);
	if (env_t->content->value)
		free(env_t->content->value);
	free(env_t->content);
	free(env_t);
	//env_t = NULL;
	//return (env_next);
}

char	**new_env_malloc(char **env, int len)
{
	int		j;
	char	**new_env;
	char	*tmp;

	new_env = malloc((len + 1) * sizeof(char *));
	new_env[len] = NULL;
	j = -1;
	while (++j < len)
		new_env[j] = ft_strdup(env[j]);
	return (new_env);
}

int		check_env_line(char **env, char *key)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
		//проверить
		while (env[i][j] != '=')
			j++;
		if (!ft_strncmp(env[i], key, j))
			return (1);
		i++;
	}
	return (0);
}

char	**rewrite_env_parse(t_env *env_export, char **new_env, char **env)
{
	t_env	*ptr;
	char	*tmp;
	char	**rewrite_env;
	int		len;

	if (!new_env)
	{
		new_env = new_env_malloc(env, ft_counter_env(env));
		return (new_env);
	}
	ptr = env_export;
	len = ft_counter_env(new_env);
	while (ptr)
	{
		if (ptr->content->value && !check_env_line(new_env, ptr->content->key))
		{
			rewrite_env = new_env_malloc(new_env, len + 1);
			tmp = ft_strjoin(ptr->content->key, "=");
			rewrite_env[len] = ft_strjoin(tmp, ptr->content->value);
			free(tmp);
			free_array((void **)new_env);
			new_env = NULL;
			return (rewrite_env);
		}
		ptr = ptr->next;
	}
	return (new_env);
}

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
	int		i;
	char	**new_env;
	char	*tmp;

	new_env = malloc((len + 1) * sizeof(char *));
	new_env[len] = NULL;
	j = 0;
	i = 0;
	while (j < len)
	{
		if (!ft_strncmp(env[i], "OLDPWD", check_equals_sign(env[i]) >
				6 ? check_equals_sign(env[i]) : 6))
		{
			//write(1, "test\n", 5);
			new_env[j++] = ft_strdup("OLDPWD");
			i++;	
		}
		else
			new_env[j++] = ft_strdup(env[i++]);
	}
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

t_env		*check_export_line(t_env *env, char *str)
{
	t_env *ptr;
	int len;

	ptr = env;
	len = check_equals_sign(str);
	while (ptr)
	{
		if (ptr->content->value && !ft_strncmp(ptr->content->key, str, ft_strlen(ptr->content->key) >
				len ? ft_strlen(ptr->content->key) : len))
		{
			if (!ft_strncmp(ptr->content->value, str + len, 0))
				return (env);
			return (ptr);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

char	**rewrite_env_parse(t_env **env_export, char **new_env)
{
	t_env	*ptr;
	t_env	*test;
	char	*tmp;
	char	**rewrite_env;
	int		len;
	int i;
	int j;

	ptr = *env_export;
	len = 0;
	//len[0] = ft_counter_env(new_env);
	while (ptr)
	{
		if (ptr->content->value)
			len++;
		ptr = ptr->next;
	}
	rewrite_env = (char **)malloc(sizeof(char *) * (len + 1));
	rewrite_env[len] = NULL;
	i = 0;
	j = -1;
	ptr = *env_export;
	while (new_env[++j] && i < len)
	{
		test = check_export_line(ptr, new_env[j]);
		if (test == *env_export)
			rewrite_env[i++] = ft_strdup(new_env[j]);
		else if (test != *env_export && test)
		{
			tmp = ft_strjoin(test->content->key, "=");
			rewrite_env[i++] = ft_strjoin(tmp, test->content->value);
			free(tmp);
		}
	}
	ptr = *env_export;
	while (ptr && i < len)
	{
		if (!check_env_line(rewrite_env, ptr->content->key) && ft_strncmp(ptr->content->key, "OLDPWD", ft_strlen(ptr->content->key) >
				6 ? ft_strlen(ptr->content->key) : 6))
		{
			write(1, ptr->content->key, ft_strlen(ptr->content->key));
			tmp = ft_strjoin(ptr->content->key, "=");
			rewrite_env[i++] = ft_strjoin(tmp, ptr->content->value);
			free(tmp);
		}
		ptr = ptr->next;
	}
	if (new_env)
		free_array((void **)new_env);
	//write(1, ptr->content->key, ft_strlen(ptr->content->key));
	return (rewrite_env);
}

#include "../includes/minishell.h"

int		ft_counter_env(char **env)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	return (i);
}

int		check_equals_sign(char *argv)
{
	int i;

	i = 0;
	while (argv[i] != '=' && argv[i] != '\0')
		i++;
	return (i);
}

char		*get_env(t_env *env, char *str)
{
	int 		i;
	char 		*p_str;
	t_env		*ptr;

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

char		*get_env_char(char **env, char *str)
{
	int i;
	char *ptr;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str) > check_equals_sign(env[i])
									? ft_strlen(str) : check_equals_sign(env[i])))
		{
			ptr = env[i];
			return (ptr + (ft_strlen(str) + 1));
		}
	}
	return (NULL);
}

char	**new_env_malloc(char **env, int len)
{
	int		j;
	int		i;
	char	**new_env;
	char	*tmp;


	new_env = (char **)malloc((len + 1) * sizeof(char *));
	new_env[len] = NULL;
	j = 0;
	i = 0;
	while (j < len && env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD", check_equals_sign(env[i]) >
				6 ? check_equals_sign(env[i]) : 6))
		{
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
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (!ft_strncmp(env[i], key, j > ft_strlen(key) ? j : ft_strlen(key)))
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
	int i = 0;
	len = check_equals_sign(str);
	while (ptr)
	{
		if (ptr->content->value && !ft_strncmp(ptr->content->key, str, ft_strlen(ptr->content->key) >
				len ? ft_strlen(ptr->content->key) : len))
		{
			if (!ft_strncmp(ptr->content->value, str + (len + 1), 0))
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
	int i_safe;

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
		if (test && test == ptr)
			rewrite_env[i++] = ft_strdup(new_env[j]);
		else if (test && test != ptr)
		{
			tmp = ft_strjoin(test->content->key, "=");
			rewrite_env[i++] = ft_strjoin(tmp, test->content->value);
			free(tmp);
		}
	}
	i_safe = i;
	while (i_safe < len)
        rewrite_env[i_safe++] = NULL;
	ptr = *env_export;
	while (ptr && i < len)
	{
		if (ptr->content->value && !check_env_line(rewrite_env, ptr->content->key))
		{
			tmp = ft_strjoin(ptr->content->key, "=");
			rewrite_env[i++] = ft_strjoin(tmp, ptr->content->value);
			free(tmp);
		}
		ptr = ptr->next;
	}
	if (new_env)
		free_array((void **)new_env);
	return (rewrite_env);
}

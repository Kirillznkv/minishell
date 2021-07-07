#include "../includes/minishell.h"

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

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
		if (!ft_strncmp(env[i], "OLDPWD", check_equals_sign(env[i])
				> 6 ? check_equals_sign(env[i]) : 6))
		{
			new_env[j++] = ft_strdup("OLDPWD");
			i++;
		}
		else
			new_env[j++] = ft_strdup(env[i++]);
	}
	return (new_env);
}

void	write_null_env(char **env, int len, int tmp)
{
	int	i;

	i = tmp;
	while (i < len)
		env[i++] = NULL;
}

void	write_env_from_export(t_env *env_export,
		char **rewrite_env, int i, int len)
{
	t_env	*ptr;
	char	*tmp;

	ptr = env_export;
	while (ptr && i < len)
	{
		if (ptr->content->value
			&& !check_env_line(rewrite_env, ptr->content->key))
		{
			tmp = ft_strjoin(ptr->content->key, "=");
			rewrite_env[i++] = ft_strjoin(tmp, ptr->content->value);
			free(tmp);
		}
		ptr = ptr->next;
	}	
}

static int	rewrite_env_from_env(t_env *env,
		char **rewrite_env, int len, char **new_env)
{
	int		i;
	int		j;
	t_env	*ptr;
	t_env	*tmp_l;
	char	*tmp;

	i = 0;
	j = -1;
	ptr = env;
	while (new_env[++j] && i < len)
	{
		tmp_l = check_export_line(ptr, new_env[j]);
		if (tmp_l && tmp_l == ptr)
			rewrite_env[i++] = ft_strdup(new_env[j]);
		else if (tmp_l && tmp_l != ptr)
		{
			tmp = ft_strjoin(tmp_l->content->key, "=");
			rewrite_env[i++] = ft_strjoin(tmp, tmp_l->content->value);
			free(tmp);
		}
	}
	return (i);
}

char	**rewrite_env_parse(t_env **env_export, char **new_env)
{
	t_env	*ptr;
	char	**rewrite_env;
	int		len;
	int		i;

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
	i = rewrite_env_from_env(*env_export, rewrite_env, len, new_env);
	write_null_env(rewrite_env, len, i);
	write_env_from_export(*env_export, rewrite_env, i, len);
	if (new_env)
		free_array((void **)new_env);
	return (rewrite_env);
}

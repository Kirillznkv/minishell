#include "../../includes/minishell.h"

t_env	*check_repeat_export(t_env *env_export, char *key)
{
	t_env	*ptr;
	t_env	*tmp;
	int		i;

	i = check_equals_sign(key);
	ptr = env_export;
	if (!ft_strncmp(ptr->content->key, key, ft_strlen(ptr->content->key)
			> i ? ft_strlen(ptr->next->content->key) : i))
		return (ptr);
	while (ptr->next)
	{
		if (!ft_strncmp(ptr->next->content->key, key,
				ft_strlen(ptr->next->content->key) > i
				? ft_strlen(ptr->next->content->key) : i))
			return (ptr->next);
		ptr = ptr->next;
	}
	return (NULL);
}

int	check_valid_identifier(char *id, int fd)
{
	int	i;

	i = 0;
	if (id[0] == '=' || ft_isdigit(id[0]) || id[0] == '-')
	{
		if (id[0] == '-')
			ft_error(id, 6, 2, fd);
		else
			ft_error(id, 5, 1, fd);
		return (0);
	}
	return (1);
}

t_env	*ft_create_env(char **env)
{
	t_env	*ptr;
	t_env	*env_export;
	int		i;

	env_export = new_elem_env();
	ptr = env_export;
	i = 0;
	write_env(ptr, env[i]);
	while (env[++i])
		add_elem_env(ptr, new_elem_env(), write_env, env[i]);
	return (env_export);
}

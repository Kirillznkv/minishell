#include "../includes/minishell.h"

int	ft_counter_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	*get_env(t_env *env, char *str)
{
	int			i;
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

char	*get_env_char(char **env, char *str)
{
	int		i;
	char	*ptr;

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

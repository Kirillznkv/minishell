#include "../../includes/minishell.h"

void	write_env_value(t_env *env_export, char *env, int i)
{
	int	j;
	int	tmp;

	j = 0;
	tmp = i;
	while (env[tmp++])
		j++;
	env_export->content->value = (char *)malloc(sizeof(char) * (j) + 1);
	j = 0;
	while (env[i])
	{
		(env_export->content)->value[j] = env[i];
		j++;
		i++;
	}
	env_export->content->value[j] = '\0';
}

int	write_env_key(t_env *env_export, char *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	env_export->content->key = (char *)malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		env_export->content->key[j] = env[j];
		j++;
	}
	env_export->content->key[j] = '\0';
	if (env[i] == '\0')
		return (0);
	return (j + 1);
}

void	write_env(t_env *env_export, char *env)
{
	int	i;

	i = write_env_key(env_export, env);
	if (i > 0 && ft_strncmp(env, "OLDPWD", check_equals_sign(env)
			> 6 ? check_equals_sign(env) : 6))
		write_env_value(env_export, env, i);
}

#include "../../includes/minishell.h"

t_env			*new_elem_env(void)
{
	t_env		*new_elem;

	if (!(new_elem = (t_env *)malloc(sizeof(t_env))))
		ft_error(3);
	new_elem->next = NULL;
	return (new_elem);
}

void				add_elem_env(t_env *env, t_env *new_env)
{
	t_env		*ptr;

	ptr = env;
	if (env == NULL)
		env = new_env;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_env;
	}
}

void		write_env_value(t_env *env_export, char *env, int i)
{
	int j;
	int tmp;

	j = 0;
	tmp = i;
	while (env[tmp++])
		j++;
	env_export->value = (char *)malloc(sizeof(char) * j);
	j = 0;
	while (env[i])
	{
		env_export->value[j] = env[i];
		j++;
		i++;
	}
	env_export->value[j] = '\0';
}
int		write_env_key(t_env *env_export, char *env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env[i] != '=')
		i++;
	env_export->key = (char *)malloc(sizeof(char) * i);
	while (j < i)
	{
		env_export->key[j] = env[j];
		j++;
	}
	env_export->key[j] = '\0';
	return (j + 1);
}

void		write_env_export(t_env *env_export, char *env)
{
	int i;

	i = write_env_key(env_export, env);
	write_env_value(env_export, env, i);
	printf("%s\n", env_export->key);
	printf("%s\n", env_export->value);
}


void	ft_export_shell(char **env)
{
	int i;

	i = 0;
	t_env	*env_export;
	env_export = new_elem_env();
	while (env[i])
	{
		//printf("%s\n", env[i]);
		write_env_export(env_export, env[i]);
		add_elem_env(env_export, new_elem_env());
		i++;
	}
	// t_env	*env_ptr;
	// env_ptr = env_export;
	// while (env_ptr)
	// {
	// 	printf("%s\n", env_ptr->key);
	// 	printf("%s\n", env_ptr->value);
	// 	env_ptr = env_ptr->next;
	// }
	
	//ft_env_sort(env);

	// while (env[i])
	// {
	// 	ft_putstr("declare -x ");
	// 	ft_putstr(env[i++]);
	// 	ft_putchar('\n');
	// }
}
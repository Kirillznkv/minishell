
#include "../../includes/minishell.h"

static void		rewrite_env_pwd(t_env *env, const char *str, char *pwd)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content->key, str, 0))
		{
			free(ptr->content->value);
			ptr->content->value = NULL;
			ptr->content->value = ft_strdup(pwd);
		}
		ptr = ptr->next;
	}
}

static int		check_pwd_and_home(t_env *env, const char *str)
{
	t_env		*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content->key, str, 0))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void			ft_cd_shell(char *argv, t_env *env)
{
	char	*new_pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	chdir(argv);
	if (check_pwd_and_home(env, "PWD"))
		rewrite_env_pwd(env, "OLDPWD", old_pwd);
	else
		rewrite_env_pwd(env, "OLDPWD", "");
	new_pwd = getcwd(NULL, 0);
	rewrite_env_pwd(env, "PWD", new_pwd);
	free(new_pwd);
	free(old_pwd);
}
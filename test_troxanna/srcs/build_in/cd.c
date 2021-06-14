
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
	free(pwd);
}

void			ft_cd_shell(char *argv, t_env *env)
{
	char	*new_pwd;
	char	*old_pwd;
	//обработать случай, когда нет env HOME и PWD
	old_pwd = getcwd(NULL, 0);
	chdir(argv);
	rewrite_env_pwd(env, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	rewrite_env_pwd(env, "PWD", new_pwd);
}
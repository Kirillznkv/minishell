
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
	char	*tmp_pwd;
	//обработать случай, когда удаляем PWD - в OLDPWD не должно что либо записываться
	tmp_pwd = getenv("PWD");
	printf("%s\n", tmp_pwd);
	old_pwd = getcwd(NULL, 0);
	chdir(argv);
	if (tmp_pwd)
		rewrite_env_pwd(env, "OLDPWD", old_pwd);
	else
		rewrite_env_pwd(env, "OLDPWD", "");
	new_pwd = getcwd(NULL, 0);
	rewrite_env_pwd(env, "PWD", new_pwd);
}
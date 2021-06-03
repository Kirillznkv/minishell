#ifndef	MINISHELL_H
# define MINISHELL_H

# include "../../kshanti/includes_parser/structures.h"
# include "../../kshanti/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>

typedef	struct 				s_content
{
	char					*key;
	char					*value;
	//хранить указатель на часть строки, которую получаю из env
}							t_content;

typedef	struct 				s_env
{
	t_content				content;
	struct s_env			*next;
}							t_env;

void		ft_putchar(char c);
char		**ft_split(char *s, char c);
void		ft_putstr(char *s);
int			ft_counter_env(char **env);
int			ft_counter_lstenv(t_env *lst);
void		delet_elem_env(t_env *env, t_env *env_unset);
void		ft_error(int n);
void		ft_print_env(t_env *env_export, int ex);
void		ft_env_shell(t_env *env, int c_env);
void		ft_env_sort(t_env *env_export, int i);
void		ft_export_shell(t_env *env_export, char **argv, int argc, int c_env);
char		*ft_strnstr(const char *s, const char *find, size_t slen);
void		ft_pwd_shell(char **env);
void		ft_echo_shell(char **argv);
void		ft_unset_shell(t_env *env, char **argv, int argc, int c_env);
void		ft_cd_shell(char **env, char *argv);
t_env 		*ft_create_env(char **env);
void		exec_run(char **argv, char **env);
void		ft_exit_shell();

#endif
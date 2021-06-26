#ifndef	MINISHELL_H
# define MINISHELL_H

# include "../../kshanti/includes_parser/structures.h"
//# include "../../kshanti/includes_parser/parser.h"
# include "../../kshanti/libft/libft.h"
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>

int			error_code_dollar;

typedef	struct 				s_content
{
	char					*key;
	char					*value;
	//хранить указатель на часть строки, которую получаю из env
}							t_content;

typedef	struct 				s_env
{
	t_content				*content;
	struct s_env			*next;
}							t_env;

void		ft_putchar(char c);
char		**ft_split(char *s, char c);
void		ft_putstr(char *s);
int			ft_counter_env(char **env);
int			ft_counter_lstenv(t_env *lst);
t_env		*new_elem_env(void);
void		free_char_array(char **env);
void		delet_elem_env(t_env *env, t_env *env_unset);
t_env		*free_t_env(t_env *env_t);
void		ft_error(char *name, int n);
void		ft_print_env(t_env *env_export, int ex, int fd);//
void		ft_env_shell(t_env *env, int fd);//
void		ft_env_sort(t_env *env_export, int i);
void		ft_export_shell(t_env *env_export, char **argv, int argc, int fd);//
char		*ft_strnstr(const char *s, const char *find, size_t slen);
void		ft_pwd_shell(int fd, char **env);//
void		ft_echo_shell(char **argv, int fd, t_env *env);//
void		ft_unset_shell(t_env *env, char **argv, int argc);
void		ft_cd_shell(char *argv, t_env *env);
char		**rewrite_env_parse(t_env *env);
t_env 		*ft_create_env(char **env, t_env *env_export);
void		exec_run(t_commands *argv, char **env);//
void		ft_exit_shell();
char		**new_env_malloc(char **env);
void		parse_command(t_commands *cmd, char ***env, t_env *env_main);

#endif
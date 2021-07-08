#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../kshanti/includes_parser/structures.h"
# include "../../kshanti/libft/libft.h"
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

int			g_error_code_dollar;

typedef struct s_content
{
	char			*key;
	char			*value;
}	t_content;

typedef struct s_env
{
	t_content		*content;
	struct s_env	*next;
}	t_env;

char		**ft_split(char *s, char c);
int			ft_counter_env(char **env);
int			ft_counter_lstenv(t_env *lst);
t_env		*new_elem_env(void);
void		add_elem_env(t_env *env, t_env *new_env,
				void (*wrt)(t_env *, char *), char *s);
void		free_array(void **array);
t_env		*delete_head(t_env *root);
t_env		*delet_elem(t_env *lst, t_env *root);
void		free_t_env(t_env *env_t);
int			check_equals_sign(char *argv);
void		ft_error(char *name, int n, int err_code, int fd);
void		ft_error_exec(char *name, int n, int err_code, int fd);
int			**create_pipe_fd(int count);
int			check_env_line(char **env, char *key);
t_env		*check_repeat_export(t_env *env_export, char *key);
int			check_valid_identifier(char *id, int fd);
char		*get_env_char(char **env, char *str);
char		*get_env(t_env *env, char *str);
void		ft_env_shell(char **env, int fd, t_env *env_main);
void		ft_export_shell(t_env **env_export, char **argv, int argc, int fd);
void		ft_pwd_shell(int fd, t_env *env);
void		ft_echo_shell(char **argv, int fd, t_env *env);
void		ft_unset_shell(t_env **env, char **argv, int argc, int fd);
void		ft_cd_shell(char **argv, t_env *env, int fd);
char		**rewrite_env_parse(t_env **env_export, char **new_env);
t_env		*ft_create_env(char **env);
void		exec_run(t_commands *cmd, char **env);
void		ft_exit_shell(int fd, char **argv, int argc);
char		**new_env_malloc(char **env, int len);
int			parse_command(t_commands *cmd, char ***env, t_env **env_main);
void		execute_pipe(t_commands *cmd, char ***env, t_env **env_main);
void		start_cmd(t_commands *cmd, char ***env, t_env **env_main);
t_env		*check_export_line(t_env *env, char *str);
void		write_env(t_env *env_export, char *env);

#endif
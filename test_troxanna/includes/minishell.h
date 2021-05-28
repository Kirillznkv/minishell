#ifndef	MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

typedef	struct 				s_content
{
	char					*key;
	char					*value;
}							t_content;

typedef	struct 				s_env
{
	t_content				content;
	struct s_env			*next;
}							t_env;

void		ft_putchar(char c);
void		ft_bzero(void *s, size_t n);
char		*ft_stpcpy(char *dst, const char *src);
char		*ft_strdup(char *str);
int			ft_strlen(char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		**ft_split(char *s, char c);
void		ft_putstr(char *s);
void		ft_error(int n);
int			ft_strcmp(const char *str1, const char *str2);
int			ft_isalpha(int ch);
void		ft_env_shell(char **env);
void		ft_env_sort(t_env *env_export, int i);
void		ft_export_shell(char **env);
char		*ft_strnstr(const char *s, const char *find, size_t slen);
void		ft_pwd_shell(char **env);
void		ft_echo_shell(char **argv);
void		ft_unset_shell(char **env, char **argv, int args);
void		ft_cd_shell(char **env, char *argv);
void		exec_run(char **argv, char **env);
void		ft_exit_shell();

#endif
#ifndef	MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef	struct 				s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

void		ft_putchar(char c);
int			ft_strlen(char *s);
void		ft_putstr(char *s);
void		ft_error(int n);
int			ft_strcmp(const char *str1, const char *str2);
int			ft_isalpha(int ch);
void		ft_env_shell(char **env);
t_env		*ft_env_sort(t_env *env_export);
void		ft_export_shell(char **env);
char		*ft_strnstr(const char *s, const char *find, size_t slen);
void		ft_pwd_shell(char **env);
void		ft_echo_shell(char **argv);
void		ft_unset_shell(char **env, char **argv, int args);

#endif
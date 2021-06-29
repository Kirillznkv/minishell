/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:52:25 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/29 23:17:58 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../../test_troxanna/includes/minishell.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "stdio.h"
# include "stdlib.h"
# include "errno.h"
# include "unistd.h"
#include "termios.h" 

# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN "\x1b[36m"
# define ANSI_COLOR_RESET "\x1b[0m"
// # define CONTROL_C -2142

void rl_replace_line();

/*-----------------------------------Errors-----------------------------------*/
void		error_control(char *str);
void		error_system(int error);
/*-----------------------------------Quotes-----------------------------------*/
void		delete_quotes(char **p_command_line, size_t beg_quotes, size_t end_quotes);
void		replace_single_quotes(char **p_command_line, size_t *begin_quotes);
void		replace_double_quotes(char **p_command_line, char **env, size_t *begin_quotes);
/*-----------------------------------Dollar-----------------------------------*/
void		past_error_code(char **p_command_line, size_t *i);
void		replace_dollar(char **p_command_line, char **env, size_t *begin_dollar);
void		replace_dollar_from_env(char **p_command_line, char **env, size_t *beg_dollar);
int			replace_only_one_dollar(char **p_command_line, size_t *beg_dollar);
int			replace_undefine_dollar(char **p_command_line, size_t *beg_dollar);
void		replace_dollar_word(char **p_command_line, char *new_dollar_word, int beg_dollar, int end_dollar_word);
char		*get_new_dollar_word(char **env, char *dollar_word);
char		*get_second_env_word(char *env_line);
int			check_env_word(char *env_line, char *dollar_word);
/*-----------------------------------Parser-----------------------------------*/
void		parser(char *commands_line, char ***env, t_env *env_main);
t_commands	*get_one_command(char **p_commands_line, char **env);
void		save_command(char **p_command_line, size_t *i, t_commands *command);
void		check_end_word(char **p_command_line, size_t *i, t_commands **command);
void		replace_normal_char(char **p_command_line, size_t *i);
int			replace_back_slash(char **p_command_line, size_t *i);
/*-----------------------------------Preparser--------------------------------*/
int			preparser(char *commands_line);
int			check_single_quotes(char *str, int *i);
int			check_double_quotes(char *str, int *i);
int			check_back_slash(char *str, int *i);
int			check_back_slash_at_the_end(char *commands_line);
/*--------*/
int			precheck_redirect(char *str, int *i);
int			base_delimiter(char *str, int i);
int			quotes_delimiter(char *str, int i);
int			preparser_delimiter(char *str, int i);
/*-----------------------------------Utils------------------------------------*/
int			check_command(t_commands *command);
char		**malloc_argv(int argc, char **argv);
void		skip_spases_tabs(char **p_command_line, size_t begin);
t_commands	*init_command(void);
void		delete_one_char(char **p_command_line, size_t i);
void		free_command(t_commands **command);
void		fd_control(t_commands **command);
/*-----------------------------------Redirect---------------------------------*/
void		replace_redirect(t_commands *command, char **p_command_line, size_t *i);
void		redirect(t_commands *command, char **p_command_line, size_t *i);
void		back_redirect(t_commands *command, char **p_command_line, size_t *i);
void		add_fd(t_commands *command, int new_fd);
void		double_back_redirect(t_commands *command, char *name);

#endif
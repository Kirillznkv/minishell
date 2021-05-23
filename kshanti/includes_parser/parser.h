/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:52:25 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/23 21:10:34 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"
# include "../libft/libft.h"
# include "stdio.h"
# include "stdlib.h"
# include "errno.h"

/*-----------------------------------Errors-----------------------------------*/
void			error_control(char *str);
void			error_system(int error);
/*-----------------------------------Quotes-----------------------------------*/
void			delete_quotes(char **p_command_line, size_t beg_quotes, size_t end_quotes);
void			replace_single_quotes(char **p_command_line, size_t *begin_quotes);
void			delete_one_char(char **str, size_t i_delete);
void			replace_double_quotes(char **p_command_line, char **env, size_t *begin_quotes);
/*-----------------------------------Dollar-----------------------------------*/
void			replace_dollar(char **p_command_line, char **env, size_t *begin_dollar);
void			replace_dollar_from_env(char **p_command_line, char **env, size_t *beg_dollar);
int				replace_only_one_dollar(char **p_command_line, size_t *beg_dollar);
int				replace_undefine_dollar(char **p_command_line, size_t *beg_dollar);
void			replace_dollar_word(char **p_command_line, char *new_dollar_word, int beg_dollar, int end_dollar_word);
char			*get_new_dollar_word(char **env, char *dollar_word);
char			*get_second_env_word(char *env_line);
int				check_env_word(char *env_line, char *dollar_word);
/*-----------------------------------Parser-----------------------------------*/
t_commands		*parser(char *commands_line, char **env);
void			skip_spases_tabs(char **p_command_line, size_t begin);
void			replace_spases_tabs_whis_spase(char **p_command_line, size_t *begin);
/*-----------------------------------Preparser--------------------------------*/
void			preparser(char *commands_line);
void			check_single_quotes(char *str, int *i);
void			check_double_quotes(char *str, int *i);

#endif
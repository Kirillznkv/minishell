/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:52:25 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/14 19:32:09 by kshanti          ###   ########.fr       */
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
/*-----------------------------------Parser-----------------------------------*/
t_commands		*parser(char *commands_line, char **env);
/*-----------------------------------Preparser--------------------------------*/
void			preparser(char *commands_line);
void			check_single_quotes(char *str, int *i);
void			check_double_quotes(char *str, int *i);

#endif
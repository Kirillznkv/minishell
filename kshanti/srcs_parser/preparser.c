/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:30:12 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/01 20:50:01 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

void		check_single_quotes(char *str, int *i)
{
	if (str[*i] != '\'')
		return ;
	(*i)++;
	while (str[*i] && !(str[*i] == '\'' && str[*i - 1] != '\\'))
		(*i)++;
	if (!str[*i])
		error_control("Single quote not closed");
}

void		check_double_quotes(char *str, int *i)
{
	if (str[*i] != '\"')
		return ;
	(*i)++;
	while (str[*i] && !(str[*i] == '\"' && str[*i - 1] != '\\'))
		(*i)++;
	if (!str[*i])
		error_control("Double quote not closed");
}

int		check_back_slash(char *str, int *i)
{
	if (str[*i] != '\\')
		return (0);
	(*i)++;
	return (1);
}

void		preparser(char *commands_line)
{
	int		i;

	i = -1;
	if (commands_line[ft_strlen(commands_line) - 1] == '\\')
		error_control("Back slash at the end of the line");
	while (commands_line[++i])
	{
		if (check_back_slash(commands_line, &i))
			continue ;
		check_single_quotes(commands_line, &i);
		check_double_quotes(commands_line, &i);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:56:35 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/16 20:24:03 by kshanti          ###   ########.fr       */
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

void		preparser(char *commands_line)
{
	int		i;

	i = -1;
	if (commands_line[ft_strlen(commands_line) - 1] == '\\')
		error_control("Back slash at the end of the line");
	while (commands_line[++i])
	{
		check_single_quotes(commands_line, &i);
		check_double_quotes(commands_line, &i);
	}
}

void		skip_spases_tabs(char **str)
{
	while (**str == ' ' || **str == '\t')
		str = *str + 1;
}

t_commands	*get_one_command(char **p_commands_line, char ** env)
{
	t_commands	*command;
	char		*command_line;

	skip_spases_tabs(p_commands_line);
	command_line = *p_commands_line;
	while (*command_line && *command_line != '\n' && *command_line != ';')
	{
		replace_single_quotes();//  '
		replace_double_quotes();//  "
		replace_dolar();//          $
	}
}

t_commands	*parser(char *commands_line, char **env)
{
	t_commands		*first;

	if (!commands_line)
		error_control("Commands line is NULL");
	preparser(commands_line);
	while (*commands_line)
	{
		ft_lstadd_back(&first, get_one_command(&commands_line, env));
	}
	return (NULL);
}
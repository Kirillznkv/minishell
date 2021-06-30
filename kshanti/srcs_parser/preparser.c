/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:30:12 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/30 21:43:24 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

int		check_single_quotes(char *str, int *i)
{
	if (str[*i] != '\'')
		return (0);
	(*i)++;
	while (str[*i] && !(str[*i] == '\'' && str[*i - 1] != '\\'))
		(*i)++;
	if (!str[*i])
	{
		write(1, "Error: Single quote not closed\n", 32);
		return (1);
	}
	return (0);
}

int		check_double_quotes(char *str, int *i)
{
	if (str[*i] != '\"')
		return (0);
	(*i)++;
	while (str[*i] && !(str[*i] == '\"' && str[*i - 1] != '\\'))
		(*i)++;
	if (!str[*i])
	{
		write(1, "Error: Double quote not closed\n", 32);
		return (1);
	}
	return (0);
}

int			check_back_slash(char *str, int *i)
{
	if (str[*i] != '\\')
		return (0);
	(*i)++;
	return (1);
}

int		check_back_slash_at_the_end(char *commands_line)
{
	size_t	i;
	size_t	column_back_slash;

	i = ft_strlen(commands_line) - 1;
	column_back_slash = 1;
	if (commands_line[i--] != '\\')
		return (0);
	while (i && commands_line[i--] == '\\')
		column_back_slash++;
	if (column_back_slash % 2)
	{
		write(1, "Error: Back slash at the end of the line\n", 42);
		return (1);
	}
	return (0);
}

int		preparser(char *commands_line)
{
	int		i;

	i = -1;
	check_back_slash_at_the_end(commands_line);
	while (commands_line[++i])
	{
		if (precheck_redirect(commands_line, &i))
			return (1);
		if (check_back_slash(commands_line, &i))
			continue ;
		if (check_single_quotes(commands_line, &i))
			return (1);
		if (check_double_quotes(commands_line, &i))
			return (1);
		if (commands_line[i] == '|' && commands_line[i + 1] == '|')
		{
			write(1, "syntax error near unexpected token '|'\n", 40);
			error_code_dollar = 258;
			return (1);
		}
	}
	return (0);
}

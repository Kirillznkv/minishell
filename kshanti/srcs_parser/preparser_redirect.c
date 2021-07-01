/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 18:54:41 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/01 21:30:16 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

int	base_delimiter(char *str, int i)
{
	int		ch;

	ch = str[i];
	if (ch == '\0')
		return (wr_er("bash: syntax error near unexpected token `newline'\n", \
																		258));
	if (ch == '|')
		return (wr_er("bash: syntax error near unexpected token `|'\n", 258));
	if (ch == ';')
		return (wr_er("bash: syntax error near unexpected token `;'\n", 258));
	if (ch == '<' || ch == '>')
		return (wr_er("bash: syntax error near unexpected token `<'\n", 258));
	return (0);
}

int	quotes_delimiter(char *str, int i)
{
	int		ch;
	int		col;

	col = 0;
	if (!(str[i] == '\'' || str[i] == '"'))
		return (0);
	while (str[i] == '\'' || str[i] == '"')
	{
		while (str[i] == '\'' && ++i)
			col++;
		if (col % 2)
			return (0);
		while (str[i] == '\"' && ++i)
			col++;
		if (col % 2)
			return (0);
	}
	ch = str[i];
	if (ch == ' ' || ch == '|' || ch == '<' || ch == '>' || \
		ch == '\t' || ch == '\0' || ch == ';')
		return (wr_er("bash: : No such file or directory\n", 1));
	return (0);
}

int	preparser_delimiter(char *str, int i)
{
	if (base_delimiter(str, i))
		return (1);
	if (quotes_delimiter(str, i))
		return (1);
	return (0);
}

int	precheck_redirect(char *str, int *i)
{
	if (str[*i] != '>' && str[*i] != '<')
		return (0);
	if (str[*i] == '<')
	{
		(*i)++;
		if (str[*i] == '<')
			(*i)++;
	}
	else if (str[*i] == '>')
	{
		(*i)++;
		if (str[*i] == '>')
			(*i)++;
	}
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	return (preparser_delimiter(str, *i));
}

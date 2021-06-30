/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:35:57 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/30 21:26:02 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

void		delete_quotes(char **p_command_line, size_t beg_quotes,
							size_t end_quotes)
{
	char	*first_part;
	char	*second_part;
	char	*third_part;
	char	*save_to_free;

	first_part = ft_substr(*p_command_line, 0, beg_quotes);
	second_part = ft_substr(*p_command_line, beg_quotes + 1,
							end_quotes - beg_quotes - 1);
	third_part = ft_substr(*p_command_line, end_quotes + 1, -1);
	free(*p_command_line);
	*p_command_line = ft_strjoin(first_part, second_part);
	save_to_free = *p_command_line;
	*p_command_line = ft_strjoin(*p_command_line, third_part);
	free(first_part);
	free(second_part);
	free(third_part);
	free(save_to_free);
}

void		replace_single_quotes(char **p_command_line, size_t *begin_quotes)
{
	size_t	end_quotes;
	char	*command_line;

	command_line = *p_command_line;
	if (command_line[*begin_quotes] != '\'')
		return ;
	end_quotes = *begin_quotes + 1;
	while (command_line[end_quotes] != '\'')
		end_quotes++;
	delete_quotes(p_command_line, *begin_quotes, end_quotes);
	*begin_quotes = end_quotes - 1;
}

void		replace_double_quotes(char **p_command_line, char **env,
									size_t *begin_quotes)
{
	size_t	end_quotes;
	char	*command_line;

	end_quotes = *begin_quotes + 1;
	command_line = *p_command_line;
	if (command_line[*begin_quotes] != '\"')
		return ;
	while (command_line[end_quotes] != '\"')
	{
		if (command_line[end_quotes] == '\\' &&
			command_line[end_quotes + 1] != '\"' &&
			command_line[end_quotes + 1] != '\\' &&
			command_line[end_quotes + 1] != '$')
			end_quotes++;
		else if (command_line[end_quotes] == '$')
		{;
			replace_dollar(p_command_line, env, &end_quotes);
			end_quotes--;
		}
		else if (command_line[end_quotes] == '\\')
			delete_one_char(p_command_line, end_quotes);
		command_line = *p_command_line;
		end_quotes++;
	}
	delete_quotes(p_command_line, *begin_quotes, end_quotes);
	*begin_quotes = end_quotes - 1;
}

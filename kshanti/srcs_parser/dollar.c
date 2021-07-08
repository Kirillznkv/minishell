/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:40:49 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/07 19:03:55 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

void	past_error_code(char **p_command_line, size_t *i)
{
	char	*string_error_code;
	char	*first_part;
	char	*last_part;
	char	*save_to_free;

	string_error_code = ft_itoa(g_error_code_dollar);
	first_part = ft_substr(*p_command_line, 0, *i);
	last_part = ft_substr(*p_command_line, *i, -1);
	free(*p_command_line);
	*p_command_line = ft_strjoin(first_part, string_error_code);
	save_to_free = *p_command_line;
	*p_command_line = ft_strjoin(*p_command_line, last_part);
	free(save_to_free);
	free(first_part);
	free(string_error_code);
	free(last_part);
}

int	replace_undefine_dollar(char **p_command_line, size_t *beg_dollar)
{
	size_t	i;
	char	*command_line;

	command_line = *p_command_line;
	i = *beg_dollar + 1;
	if (command_line[i] == '?')
	{
		delete_one_char(p_command_line, *beg_dollar);
		delete_one_char(p_command_line, *beg_dollar);
		past_error_code(p_command_line, beg_dollar);
		return (1);
	}
	if (command_line[i] != '@' && command_line[i] != '*' && \
		command_line[i] != '$' && command_line[i] != '!' && \
		command_line[i] != '-' && \
		command_line[i] != '#' && !ft_isdigit(command_line[i]))
		return (0);
	delete_one_char(p_command_line, *beg_dollar);
	delete_one_char(p_command_line, *beg_dollar);
	return (1);
}

int	replace_only_one_dollar(char **p_command_line, size_t *beg_dollar)
{
	size_t	i;
	char	*command_line;

	command_line = *p_command_line;
	i = *beg_dollar + 1;
	if (ft_isalnum(command_line[i]) || command_line[i] == '_')
		return (0);
	(*beg_dollar)++;
	return (1);
}

void	replace_dollar_from_env(char **p_command_line, char **env, \
								size_t *beg_dollar)
{
	size_t	end_dollar_word;
	char	*command_line;
	char	*dollar_word;
	char	*new_dollar_word;

	command_line = *p_command_line;
	end_dollar_word = *beg_dollar + 1;
	while (command_line[end_dollar_word] == '_' || \
			ft_isalnum(command_line[end_dollar_word]))
		end_dollar_word++;
	dollar_word = ft_substr(command_line, *beg_dollar + 1, \
							end_dollar_word - *beg_dollar - 1);
	new_dollar_word = get_new_dollar_word(env, dollar_word);
	if (new_dollar_word)
	{
		replace_dollar_word(p_command_line, new_dollar_word, \
							*beg_dollar, end_dollar_word);
		*beg_dollar += ft_strlen(new_dollar_word);
	}
	else
		no_dollar_word(p_command_line, *beg_dollar, end_dollar_word);
	if (dollar_word)
		free(dollar_word);
	if (new_dollar_word)
		free(new_dollar_word);
}

void	replace_dollar(char **p_command_line, char **env, size_t *begin_dollar)
{
	char	*command_line;

	command_line = *p_command_line;
	if (command_line[*begin_dollar] != '$')
		return ;
	if (replace_undefine_dollar(p_command_line, begin_dollar))
		return ;
	if (replace_only_one_dollar(p_command_line, begin_dollar))
		return ;
	replace_dollar_from_env(p_command_line, env, begin_dollar);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:40:49 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/04 21:37:34 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

int			replace_undefine_dollar(char **p_command_line, size_t *beg_dollar)
{
	size_t	i;
	char	*command_line;
	char	*first_part;
	char	*second_part;

	command_line = *p_command_line;
	i = *beg_dollar + 1;
	if (command_line[i] != '@' && command_line[i] != '*' &&
		command_line[i] != '$' && command_line[i] != '!' &&
		command_line[i] != '-' && command_line[i] != '_' &&
		command_line[i] != '#' && !ft_isdigit(command_line[i]))
		return (0);
	delete_one_char(p_command_line, *beg_dollar);
	delete_one_char(p_command_line, *beg_dollar);
	return (1);
}

int			replace_only_one_dollar(char **p_command_line, size_t *beg_dollar)
{
	size_t	i;
	char	*command_line;

	command_line = *p_command_line;
	i = *beg_dollar + 1;
	if (ft_isalpha(command_line[i]))
		return (0);
	(*beg_dollar)++;
	return (1);
}

void		replace_dollar_from_env(char **p_command_line, char **env, size_t *beg_dollar)
{
	size_t	end_dollar_word;
	char	*command_line;
	char	*dollar_word;
	char	*new_dollar_word;

	command_line = *p_command_line;
	end_dollar_word = *beg_dollar + 1;
	while (command_line[end_dollar_word] == '_' || ft_isalpha(command_line[end_dollar_word]))
		end_dollar_word++;
	dollar_word = ft_substr(command_line, *beg_dollar + 1, end_dollar_word - *beg_dollar - 1);
	new_dollar_word = get_new_dollar_word(env, dollar_word);
	if (dollar_word)
		free(dollar_word);
	replace_dollar_word(p_command_line, new_dollar_word, *beg_dollar, end_dollar_word);
	if (new_dollar_word)
		free(new_dollar_word);
	*beg_dollar += ft_strlen(new_dollar_word);
}

void		replace_dollar(char **p_command_line, char **env, size_t *begin_dollar) // need $?
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

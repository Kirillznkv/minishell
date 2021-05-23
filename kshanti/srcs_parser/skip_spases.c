/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:33:16 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/23 20:35:38 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

void		skip_spases_tabs(char **p_command_line, size_t begin)
{
	size_t	end;
	char	*command_line;
	char	*first_part;
	char	*last_part;
	char	*save_to_free;

	command_line = *p_command_line;
	end = begin;
	while (command_line[end] == ' ' || command_line[end] == '\t')
		end++;
	if (end == begin)
		return ;
	save_to_free = *p_command_line;
	first_part = ft_substr(*p_command_line, 0, begin);
	last_part = ft_substr(*p_command_line, end, -1);
	*p_command_line = ft_strjoin(first_part, last_part);
	free(save_to_free);
	free(first_part);
	free(last_part);
}

void		replace_spases_tabs_whis_spase(char **p_command_line, size_t *begin)
{
	char	*command_line;
	char	*first_part;
	char	*last_part;
	char	*save_to_free;

	command_line = *p_command_line;
	if (command_line[*begin] != ' ' && command_line[*begin] != '\t')
		return ;
	skip_spases_tabs(p_command_line, *begin);
	command_line = *p_command_line;
	if (command_line[*begin] == '\0')
		return ;
	save_to_free = *p_command_line;
	first_part = ft_substr(*p_command_line, 0, *begin);
	last_part = ft_substr(*p_command_line, *begin, -1);
	*p_command_line = ft_strjoin(first_part, " ");
	free(save_to_free);
	save_to_free = *p_command_line;
	*p_command_line = ft_strjoin(*p_command_line, last_part);
	free(save_to_free);
	free(first_part);
	free(last_part);
	(*begin)++;
}

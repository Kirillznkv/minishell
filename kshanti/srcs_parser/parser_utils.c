/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:23:29 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/07 19:24:46 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

int	replace_back_slash(char **p_command_line, size_t *i)
{
	char	*command_line;

	command_line = *p_command_line;
	if (command_line[*i] != '\\')
		return (0);
	delete_one_char(p_command_line, *i);
	(*i)++;
	return (1);
}

void	replace_normal_char(char **p_command_line, size_t *i)
{
	char	*command_line;

	command_line = *p_command_line;
	while (command_line[*i] != ' ' && command_line[*i] != '\"' && \
		command_line[*i] != '$' && command_line[*i] != '\'' && \
		command_line[*i] != '|' && command_line[*i] != '\t' && \
		command_line[*i] != ';' && command_line[*i] != '\0' && \
		command_line[*i] != '<' && command_line[*i] != '\n' && \
		command_line[*i] != '>')
		(*i)++;
}

void	save_command(char **p_command_line, size_t *i, t_commands *command)
{
	char	*save_to_free;

	if (command->name == NULL)
		command->name = ft_substr(*p_command_line, 0, *i);
	command->argv = malloc_argv(command->argc, command->argv);
	command->argv[command->argc++] = ft_substr(*p_command_line, 0, *i);
	save_to_free = *p_command_line;
	*p_command_line = ft_substr(*p_command_line, *i, -1);
	*i = 0;
	free(save_to_free);
}

int	check_command(t_commands *command)
{
	t_commands	*p;

	if (!command)
		return (0);
	p = command;
	while (p)
	{
		if (!(p->name))
		{
			if (p->next && p->fd_in == 0 && p->fd_out == 1)
				wr_er("bash: syntax error near unexpected token '|'\n", 258);
			else if (!(p->next) && p->fd_in == 0 && p->fd_out == 1)
				wr_er("bash: syntax error near unexpected token ';'\n", 258);
			return (0);
		}
		p = p->next;
	}
	return (1);
}

void	delete_one_char(char **p_command_line, size_t i)
{
	char	*first_part;
	char	*last_part;

	first_part = ft_substr(*p_command_line, 0, i);
	last_part = ft_substr(*p_command_line, i + 1, -1);
	free(*p_command_line);
	*p_command_line = ft_strjoin(first_part, last_part);
	free(first_part);
	free(last_part);
}

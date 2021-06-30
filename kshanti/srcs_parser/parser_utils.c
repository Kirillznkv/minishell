/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:15:25 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/30 21:51:52 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

int			check_command(t_commands *command)
{
	t_commands *p;

	if (!command || !(command->name))
		return (0);
	p = command;
	while (p)
	{
		if (!(p->name))
			return (0);
		p = p->next;
	}
	return (1);
}

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

void		replace_normal_char(char **p_command_line, size_t *i)
{
	char	*command_line;

	command_line = *p_command_line;
	while (command_line[*i] != ' ' && command_line[*i] != '\"' &&
		command_line[*i] != '$' && command_line[*i] != '\'' &&
		command_line[*i] != '|' && command_line[*i] != '\t' &&
		command_line[*i] != ';' && command_line[*i] != '\0' &&
		command_line[*i] != '<' && command_line[*i] != '\n' &&
		command_line[*i] != '>')
		(*i)++;
}

void		save_command(char **p_command_line, size_t *i, t_commands *command)
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

void		check_end_word(char **p_command_line, size_t *i,
							t_commands **command)
{
	char	*command_line;

	command_line = *p_command_line;
	if (command_line[*i] == ' ' || command_line[*i] == '\t' ||
		command_line[*i] == ';' || command_line[*i] == '\n' ||
		command_line[*i] == '>' || command_line[*i] == '\0' ||
		command_line[*i] == '<')
	{
		skip_spases_tabs(p_command_line, *i);
		command_line = *p_command_line;
		if (command_line[*i] == '>' || command_line[*i] == '<' ||
			(*command)->fd_flag)
		{
			replace_redirect(*command, p_command_line, i);
			if (!((*command)->fd_flag || *i == 0))
				save_command(p_command_line, i, *command);
		}
		else
			save_command(p_command_line, i, *command);
	}
	else if (command_line[*i] == '|')
	{
		delete_one_char(p_command_line, *i);
		if (*i != 0)
			save_command(p_command_line, i, *command);
		(*command)->pipe = 1;
		(*command)->next = init_command();
		fd_control(command);
		*command = (*command)->next;
		skip_spases_tabs(p_command_line, *i);
	}
}

int		replace_back_slash(char **p_command_line, size_t *i)
{
	char	*command_line;

	command_line = *p_command_line;
	if (command_line[*i] != '\\')
		return (0);
	delete_one_char(p_command_line, *i);
	(*i)++;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:56:35 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/01 17:31:18 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

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
			if ((*command)->fd_flag || *i == 0)
				replace_redirect(*command, p_command_line, i);
			else
			{
				replace_redirect(*command, p_command_line, i);
				save_command(p_command_line, i, *command);
			}
		}
		else
		{
			save_command(p_command_line, i, *command);
		}
	}
	else if (command_line[*i] == '|')
	{
		delete_one_char(p_command_line, *i);
		if (command_line[*i] == '|')
			error_control("syntax error near unexpected token '|'");
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

t_commands	*get_one_command(char **p_commands_line, char **env)
{
	size_t		i;
	t_commands	*command;
	t_commands	*first;
	char		*command_line;

	i = 0;
	first = init_command();
	command = first;
	skip_spases_tabs(p_commands_line, i);
	command_line = *p_commands_line;
	while (command_line[i] && command_line[i] != '\n' && command_line[i] != ';')
	{
		if (replace_back_slash(&command_line, &i))
		{
			check_end_word(&command_line, &i, &command);
			continue ;
		}
		replace_single_quotes(&command_line, &i);
		replace_double_quotes(&command_line, env, &i);
		replace_dollar(&command_line, env, &i);
		replace_normal_char(&command_line, &i);
		check_end_word(&command_line, &i, &command);
	}
	command->argv = malloc_argv(command->argc, command->argv);
	if (command_line[i] == ';')
	{
		*p_commands_line = ft_substr(command_line, 1, -1);
		free(command_line);
	}
	else
		*p_commands_line = command_line;
	fd_control(&first);
	return (first);
}

void		parser(char *commands_line, char ***env, t_env *env_main)
{
	t_commands		*command;

	if (!commands_line)
		return ;
	if (preparser(commands_line))
	{
		free(commands_line);
		return ;
	}
	command = NULL;
	while (*commands_line)
	{
		command = get_one_command(&commands_line, *env);
		if (check_command(command))
			start_cmd(command, env, env_main);
		if (command)
			free_command(&command);
	}
	free(commands_line);
}

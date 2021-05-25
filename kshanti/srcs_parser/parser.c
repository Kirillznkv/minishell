/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:56:35 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/25 21:56:47 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

void		replace_normal_char(char **p_command_line, size_t *i)
{
	char	*command_line;

	command_line = *p_command_line;
	while (command_line[*i] != ' ' && command_line[*i] != '\"' &&
		command_line[*i] != '$' && command_line[*i] != '\'' &&
		/*command_line[*i] != '|' && */command_line[*i] != '\t' &&
		command_line[*i] != ';' && command_line[*i] != '\0' &&
		command_line[*i] != '\n')
		(*i)++;
}

void		check_end_word(char **p_command_line, size_t *i, t_commands *command)
{
	char	*command_line;
	char	*save_to_free;

	//replace_spases_tabs_whis_spase(p_command_line, i);
	command_line = *p_command_line;
	if (command_line[*i] == ' ' || command_line[*i] == '\t' ||
		command_line[*i] == ';' || command_line[*i] == '\n' ||
		command_line[*i] == '\0')
	{
		command->argv = malloc_argv(command->argc, command->argv);
		command->argv[command->argc++] = ft_substr(*p_command_line, 0, *i);
		skip_spases_tabs(p_command_line, *i);
		save_to_free = *p_command_line;
		*p_command_line = ft_substr(*p_command_line, *i, -1);
		*i = 0;
		free(save_to_free);
	}
}

t_commands	*get_one_command(char **p_commands_line, char **env)
{
	size_t		i;
	t_commands	*command;
	char		*command_line;

	command = (t_commands*)malloc(sizeof(t_commands));
	command->argc = 0;
	command->argv = NULL;
	command->next = NULL;
	command->argv = NULL;
	i = 0;
	skip_spases_tabs(p_commands_line, i);
	command_line = *p_commands_line;
	while (command_line[i] && command_line[i] != '\n' && command_line[i] != ';')
	{
		replace_single_quotes(&command_line, &i);//       '
		replace_double_quotes(&command_line, env, &i);//  "
		replace_dollar(&command_line, env, &i);//         $
		replace_normal_char(&command_line, &i);//         word
		check_end_word(&command_line, &i, command);//     add || < > >> 
	}
	if (command_line[i] == ';')
	{
		*p_commands_line = ft_substr(command_line, 1, -1);
		free(command_line);
	}
	else
		*p_commands_line = command_line;//malloc error?
	return (command);
}

t_commands	*parser(char *commands_line, char **env)
{
	t_commands		*first;

	if (!commands_line)
		error_control("Commands line is NULL");
	preparser(commands_line);
	first = NULL;
	while (*commands_line)
	{
		first = get_one_command(&commands_line, env);
		int i = -1;
		while (++i < first->argc)
			printf("argv[%d] = |%s|\n", i, first->argv[i]);
		///Free
		i = -1;
		while (++i < first->argc)
		{
			free(first->argv[i]);
		}
		free(first->argv);
		free(first);
	}
	free(commands_line);
	return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:56:35 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/30 21:15:53 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

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

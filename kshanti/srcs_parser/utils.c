/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:15:32 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/11 19:20:37 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

char		**malloc_argv(int argc, char **argv)
{
	int		i;
	char	**new_argv;

	if (argv == NULL)
		return ((char**)calloc(1, sizeof(char*)));
	new_argv = (char**)calloc(argc + 1, sizeof(char*));
	i = -1;
	while (++i < argc)
		new_argv[i] = argv[i];
	free(argv);
	return (new_argv);
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

void		free_struct(t_commands *command)
{
	int		i;

	i = -1;
	while (++i < command->argc)
		free(command->argv[i]);
	free(command->argv);
	free(command->name);
	free(command);
}

t_commands	*init_command(void)
{
	t_commands	*command;

	command = (t_commands*)malloc(sizeof(t_commands));
	command->argc = 0;
	command->pipe = 0;
	command->argv = NULL;
	command->next = NULL;
	command->argv = NULL;
	command->name = NULL;
	return (command);
}

void		delete_one_char(char **p_command_line, size_t i)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:15:32 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/15 22:30:12 by kshanti          ###   ########.fr       */
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

t_commands	*init_command(void)
{
	t_commands	*command;

	command = (t_commands*)malloc(sizeof(t_commands));
	command->argc = 0;
	command->pipe = 0;
	command->fd_flag = 0;
	command->fd_out = 1;
	command->fd_in = 0;
	command->colun_del_fd = 0;
	command->argv = NULL;
	command->next = NULL;
	command->argv = NULL;
	command->name = NULL;
	command->delete_fd = NULL;
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

void		free_command(t_commands **p_command)
{
	t_commands	*command;

	command = *p_command;
	if (!command)
		return ;
	if (command->delete_fd)
		free(command->delete_fd);
	if (command->name)
	{
		while (command->colun_del_fd--)
			close(command->delete_fd[command->colun_del_fd]);
		free(command->name);
	}
	free_char_array(command->argv);
	if (command->next)
		free_command(&(command->next));
	free(command);
	*p_command = NULL;
}

void		check_fd_error(t_commands **p_command)
{
	int		i;
	t_commands	*command;

	i = -1;
	command = *p_command;
	while (++i < command->colun_del_fd)
	{
		if (command->delete_fd[i] == -1)
		{
			free_command(p_command);
			return ;
		}
	}
	if (command->next)
		check_fd_error(command->next);
}

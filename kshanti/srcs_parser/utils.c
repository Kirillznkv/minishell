/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:15:32 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/30 21:29:31 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

char		**malloc_argv(int argc, char **argv)
{
	int		i;
	char	**new_argv;

	if (argv == NULL)
		return ((char**)calloc(2, sizeof(char*)));
	new_argv = (char**)calloc(argc + 2, sizeof(char*));
	i = -1;
	while (++i < argc)
		new_argv[i] = argv[i];
	free(argv);
	return (new_argv);
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
	command->fd_in_name = NULL;
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
	while (command->colun_del_fd--)
	{
		if (command->delete_fd[command->colun_del_fd] != -1)
			close(command->delete_fd[command->colun_del_fd]);
	}
	if (command->delete_fd)
		free(command->delete_fd);
	if (command->fd_in_name)
		free(command->fd_in_name);
	if (command->name)
		free(command->name);
	if (command->argv)
		free_array((void **)command->argv);
	if (command->next)
		free_command(&(command->next));
	free(command);
	*p_command = NULL;
}

void		fd_control(t_commands **p_command)
{
	int		i;
	t_commands	*command;

	i = -1;
	command = *p_command;
	while (command)
	{
		while (++i < command->colun_del_fd)
		{
			if (command->delete_fd[i] == -1)
			{
				free_command(p_command);
				return ;
			}
		}
		if (command->fd_in_name && (command->argv[0] && !command->argv[1]))
		{
			command->argv = malloc_argv(command->argc, command->argv);
			command->argv[command->argc++] = ft_strjoin("./",
														command->fd_in_name);
			free(command->fd_in_name);
			command->fd_in_name = NULL;
		}
		else
			command->fd_in = 0;
		command = command->next;
	}
}

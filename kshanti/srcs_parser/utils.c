/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:15:32 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/02 19:46:29 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

int	wr_er(char *s, int error_code)
{
	write(1, s, ft_strlen(s));
	g_error_code_dollar = error_code;
	return (1);
}

char	**malloc_argv(int argc, char **argv)
{
	int		i;
	char	**new_argv;

	if (argv == NULL)
		return ((char **)calloc(2, sizeof(char *)));
	new_argv = (char **)calloc(argc + 2, sizeof(char *));
	i = -1;
	while (++i < argc)
		new_argv[i] = argv[i];
	free(argv);
	return (new_argv);
}

void	skip_spases_tabs(char **p_command_line, size_t begin)
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

	command = (t_commands *)malloc(sizeof(t_commands));
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

int	free_command(t_commands **p_command)
{
	t_commands	*command;

	command = *p_command;
	if (!command)
		return (1);
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
	return (1);
}

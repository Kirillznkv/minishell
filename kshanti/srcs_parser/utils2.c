/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:43:39 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/07 21:33:05 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

void	add_fd(t_commands *command, int new_fd)
{
	int		*new_fd_list;
	int		i;

	i = -1;
	new_fd_list = (int *)calloc(command->colun_del_fd + 1, sizeof(int));
	while (++i < command->colun_del_fd)
		new_fd_list[i] = command->delete_fd[i];
	new_fd_list[command->colun_del_fd] = new_fd;
	free(command->delete_fd);
	command->delete_fd = new_fd_list;
	command->colun_del_fd++;
}

void	redirect_error_openfile(char *file_name)
{
	write(1, "bash: ", 7);
	write(1, file_name, ft_strlen(file_name));
	write(1, ": No such file or directory\n", 29);
	g_error_code_dollar = 1;
}

int	fd_control(t_commands **p_command)
{
	t_commands	*command;
	int			i;

	i = -1;
	command = *p_command;
	while (command)
	{
		while (++i < command->colun_del_fd)
		{
			if (command->delete_fd[i] == -1)
				return (free_command(p_command));
		}
		if (command->fd_in_name && (command->argv[0] && !command->argv[1]))
		{
			command->argv = malloc_argv(command->argc, command->argv);
			command->argv[command->argc++] = ft_strjoin("./", \
														command->fd_in_name);
			free(command->fd_in_name);
			command->fd_in_name = NULL;
		}
		else
			command->fd_in = 0;
		command = command->next;
	}
	return (0);
}

void	find_redirect(t_commands *command, char **p_command_line, size_t *i)
{
	char	*command_line;

	command_line = *p_command_line;
	if (command_line[*i] == '<')
	{
		command->fd_flag = 1;
		delete_one_char(p_command_line, *i);
		command_line = *p_command_line;
		if (command_line[*i] == '<')
		{
			delete_one_char(p_command_line, *i);
			command->fd_flag = 2;
		}
	}
	else
	{
		command->fd_flag = 3;
		delete_one_char(p_command_line, *i);
		if ((*p_command_line)[*i] == '>')
		{
			delete_one_char(p_command_line, *i);
			command->fd_flag = 4;
		}
	}
	skip_spases_tabs(p_command_line, *i);
}

int	check_pipe(char *str, int *i)
{
	int	j;

	if (str[*i] != '|')
		return (0);
	j = *i + 1;
	if (str[j] == '|')
		return (wr_er("bash: syntax error near unexpected token '||'\n", 258));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:56:48 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/02 19:47:11 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

void	double_back_redirect(t_commands *command, char *name)
{
	char	*line;
	size_t	size_name;

	command->fd_in = open("./.shell_file", O_RDWR | O_CREAT | O_TRUNC, 0777);
	add_fd(command, command->fd_in);
	size_name = ft_strlen(name);
	while (get_next_line(0, &line) == 1)
	{
		if (ft_strlen(line) != size_name || ft_strncmp(line, name, size_name))
		{
			write(command->fd_in, line, ft_strlen(line));
			write(command->fd_in, "\n", 1);
			free(line);
		}
		else
		{
			free(line);
			break ;
		}
	}
	if (command->fd_in_name)
		free(command->fd_in_name);
	command->fd_in_name = ft_strdup("./.shell_file");
}

void	back_redirect(t_commands *command, char **p_command_line, size_t *i)
{
	char	*file_name;
	char	*save_to_free;
	char	*command_line;

	command_line = *p_command_line;
	skip_spases_tabs(p_command_line, *i);
	file_name = ft_substr(*p_command_line, 0, *i);
	save_to_free = *p_command_line;
	*p_command_line = ft_substr(*p_command_line, *i, -1);
	*i = 0;
	if (command->fd_flag == 1)
	{
		command->fd_in = open(file_name, O_RDONLY, 0644);
		if (command->fd_in == -1)
			redirect_error_openfile(file_name);
		if (command->fd_in_name)
			free(command->fd_in_name);
		command->fd_in_name = ft_strdup(file_name);
		add_fd(command, command->fd_in);
	}
	else if (command->fd_flag == 2)
		double_back_redirect(command, file_name);
	command->fd_flag = 0;
	free(file_name);
	free(save_to_free);
}

void	redirect(t_commands *command, char **p_command_line, size_t *i)
{
	char	*file_name;
	char	*save_to_free;
	char	*command_line;

	command_line = *p_command_line;
	skip_spases_tabs(p_command_line, *i);
	file_name = ft_substr(*p_command_line, 0, *i);
	save_to_free = *p_command_line;
	*p_command_line = ft_substr(*p_command_line, *i, -1);
	*i = 0;
	if (command->fd_flag == 3)
	{
		command->fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		add_fd(command, command->fd_out);
	}
	else if (command->fd_flag == 4)
	{
		command->fd_out = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		add_fd(command, command->fd_out);
	}
	command->fd_flag = 0;
	free(file_name);
	free(save_to_free);
}

void	find_filename_redirect(t_commands *command, char **p_com_ln, size_t *i)
{
	char	*command_line;

	command_line = *p_com_ln;
	if (command->fd_flag == 1 || command->fd_flag == 2)
		back_redirect(command, p_com_ln, i);
	else
		redirect(command, p_com_ln, i);
	skip_spases_tabs(p_com_ln, *i);
	command_line = *p_com_ln;
	if (command_line[*i] == '<' || command_line[*i] == '>')
		replace_redirect(command, p_com_ln, i);
}

void	replace_redirect(t_commands *command, char **p_command_line, size_t *i)
{
	if (!command->fd_flag)
		find_redirect(command, p_command_line, i);
	else
		find_filename_redirect(command, p_command_line, i);
}

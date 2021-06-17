/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:56:48 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/17 13:28:38 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

void		add_fd(t_commands *command, int new_fd)
{
	int		*new_fd_list;
	int		i;

	i = -1;
	new_fd_list = (int*)calloc(command->colun_del_fd + 1, sizeof(int));
	while (++i < command->colun_del_fd)
		new_fd_list[i] = command->delete_fd[i];
	new_fd_list[command->colun_del_fd] = new_fd;
	free(command->delete_fd);
	command->delete_fd = new_fd_list;
	command->colun_del_fd++;
}

void		double_back_redirect(t_commands *command, char *name)
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
}

void		back_redirect(t_commands *command, char **p_command_line, size_t *i)
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
		{
			write(1, "bash: ", 7);
			write(1, file_name, ft_strlen(file_name));
			write(1, ": No such file or directory\n", 29);
		}
		add_fd(command, command->fd_in);
	}
	else if (command->fd_flag == 2)
	{
		double_back_redirect(command, file_name);
	}
	command->fd_flag = 0;
	free(file_name);
	free(save_to_free);
}

void		redirect(t_commands *command, char **p_command_line, size_t *i)
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

void		replace_redirect(t_commands *command, char **p_command_line, size_t *i)
{
	char	*command_line;

	command_line = *p_command_line;
	if (!command->fd_flag)//Дописать препарсер на коррект ввод
	{
		if (command_line[*i] == '<')
		{
			command->fd_flag = 1;
			delete_one_char(p_command_line, *i);
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
			if (command_line[*i] == '>')
			{
				delete_one_char(p_command_line, *i);
				command->fd_flag = 4;
			}
		}
		skip_spases_tabs(p_command_line, *i);
	}
	else
	{
		if (command->fd_flag == 1 || command->fd_flag == 2)
			back_redirect(command, p_command_line, i);
		else
			redirect(command, p_command_line, i);
		skip_spases_tabs(p_command_line, *i);
		command_line = *p_command_line;
		if (command_line[*i] == '<' || command_line[*i] == '>')
		{
			replace_redirect(command, p_command_line, i);
		}
	}
}

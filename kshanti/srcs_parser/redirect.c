/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:56:48 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/15 19:18:30 by kshanti          ###   ########.fr       */
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
		add_fd(command, command->fd_in);
		
	}//если файл не открывается, то нужно вернуть нулевую структуру и позакрывать и поочищать все, как?
	else if (command->fd_flag == 2)
	{
		;
	}//fucking shit
	command->fd_flag = 0;
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
		
	}//если файл не открывается, то нужно вернуть нулевую структуру и позакрывать и поочищать все, как?
	else if (command->fd_flag == 4)
	{
		command->fd_out = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		add_fd(command, command->fd_out);
	}//fucking shit
	command->fd_flag = 0;
}

void		replace_redirect(t_commands *command, char **p_command_line, size_t *i)
{
	char	*command_line;

	command_line = *p_command_line;
	if (command_line[*i] == '<')
	{
		if (!command->fd_flag)//Дописать препарсер на коррект ввод
		{
			command->fd_flag = 1;
			delete_one_char(p_command_line, *i);
			if (command_line[*i] == '<')
			{
				delete_one_char(p_command_line, *i);
				command->fd_flag = 2;
			}
			return ;
		}
		back_redirect(command, p_command_line, i);
	}
	else if (command_line[*i] == '>')
	{
		if (!command->fd_flag)//Дописать препарсер на коррект ввод
		{
			command->fd_flag = 3;
			delete_one_char(p_command_line, *i);
			if (command_line[*i] == '>')
			{
				delete_one_char(p_command_line, *i);
				command->fd_flag = 4;
			}
			return ;
		}
		redirect(command, p_command_line, i);
	}
}

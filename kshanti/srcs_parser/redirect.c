/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:56:48 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/14 22:28:30 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

void		back_redirect(t_commands *command, char **p_command_line, size_t *i)
{
	char	*file_name;
	char	*save_to_free;
	int		one_two_redirect;
	char	*command_line;

	if (!command->fd_flag)//Дописать препарсер на коррект ввод
	{
		command->fd_flag = 1;
		return ;
	}
	one_two_redirect = 1;
	command_line = *p_command_line;
	if (command_line[*i + 1] == '<')
	{
		delete_one_char(p_command_line, *i + 1);
		one_two_redirect++;
	}
	skip_spases_tabs(p_command_line, *i);
	file_name = ft_substr(*p_command_line, 0, *i);
	save_to_free = *p_command_line;
	*p_command_line = ft_substr(*p_command_line, *i, -1);
	if (one_two_redirect == 1)
		;//если файл не открывается, то нужно пернуть нулевую структуру и позакрывать и поочищать все, как?
	else
		;//fucking shit
	*i = 0;
}

void		redirect(t_commands *command, char **p_command_line, size_t *i)
{
	if (!command->fd_flag)//Дописать препарсер на коррект ввод
	{
		command->fd_flag = 1;
		return ;
	}
}

void		replace_redirect(t_commands *command, char **p_command_line, size_t *i)
{
	char	*command_line;

	command_line = *p_command_line;
	if (command_line[*i] == '<')
		back_redirect(command, p_command_line, i);
	else if (command_line[*i] == '>')
		redirect(command, p_command_line, i);
}

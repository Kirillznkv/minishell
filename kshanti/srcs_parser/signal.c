/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:19:22 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/06 19:17:09 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

void	ctrl_c(int c)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "\e[0K\n", 6);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_slash(int c)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "\e[0K", 5);
}

void	ctrl_slash_cat(int c)
{
	write(1, "\e[1KQuit: 3\n", 13);
}

void	ctrl_d(void)
{
	write(1, "\e[1A\e[17C" "exit\n", 15);
}

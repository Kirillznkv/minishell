/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:48:55 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/19 21:18:09 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes_parser/parser.h"
#include "fcntl.h"

int		main(int argc, char **argv, char **env)
{
	char	*line;

	line = ft_strdup("' kirill ' dasha   masha");
	parser(line, env);
	return (0);
}
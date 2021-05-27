/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:48:55 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/25 20:59:21 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes_parser/parser.h"
#include "fcntl.h"

int		main(int argc, char **argv, char **env)
{
	char	*line;
	char	*line_read;

	line = ft_strdup("   sdcjns   |$PWD|    sfef  ;  skjdfs dfskjsdk ;hjk");
	line_read = (char*)calloc(10, 1);
	//read(0, line_read, 9);
	parser(line, env);
	// while (1)
	// 	;
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:48:55 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/23 20:06:26 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes_parser/parser.h"
#include "fcntl.h"

int		main(int argc, char **argv, char **env)
{
	char	*line;
	char	*line_read;

	line = ft_strdup("sdcjns |$ | sfef");
	line_read = (char*)calloc(10, 1);
	//read(0, line_read, 9);
	parser(line, env);
	free(line_read);
	free(line);
	return (0);
}
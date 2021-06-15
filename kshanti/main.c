/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:48:55 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/15 19:57:57 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes_parser/parser.h"
#include "fcntl.h"

void	free_char_array(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
	env = NULL;
}

int		main(int argc, char **argv, char **env)
{
	char	*line;

	while (get_next_line(0, &line) == 1)
	{
		parser(line, &env, NULL);
	}
	// while (1)
	// 	;
	return (0);
}
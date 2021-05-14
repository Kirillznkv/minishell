/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:48:55 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/14 19:59:18 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes_parser/parser.h"
#include "fcntl.h"

int		main()
{
	char	*line = (char*)calloc(10, 1);
	read(0, line, 9);
	parser(line, NULL);
	return (0);
}
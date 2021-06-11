/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:21:27 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/11 17:25:00 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./kshanti/includes_parser/parser.h"

int		main(int argc, char **argv, char **env)
{
	char	**new_env;
	char	**start_env;
	int		i;
	int		j;

	i = 0;
	start_env = env;
	while (*env)
	{
		i++;
		env++;
	}
	new_env = malloc(i * sizeof(char*));
	j = -1;
	while (++j < i)
		new_env[j] = ft_strdup(start_env[j]);



	
	char	*line;

	write(1, "Minishell-2.0$ ", 16);
	while (get_next_line(0, &line) == 1)
	{
		parser(line, env);
		write(1, "Minishell-2.0$ ", 16);
	}
	return (0);
}

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
	char	*line;
	t_env	*env_main;
	t_env	*ptr;

	env_main = ft_create_env(env, new_elem_env());
	ptr = env_main;
	write(1, "Minishell-2.0$ ", 16);
	while (get_next_line(0, &line) == 1)
	{
		new_env = rewrite_env_parse(env_main);
		parser(line, new_env, env_main);
		write(1, "Minixshell-2.0$ ", 16);
		//free(line); - утечек меньше, но программа ломается если > 1 аргумента
	}
	while (ptr)
		ptr = free_t_env(ptr);
	free_char_array(new_env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:21:27 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/01 19:42:59 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./kshanti/includes_parser/parser.h"

void	process_the_line(char *line, char ***new_env, t_env *env_main)
{
	if (line && *line)
		add_history(line);
	write(1, "\033[0m" ANSI_COLOR_GREEN "", 10);
	parser(line, new_env, env_main);
	write(1, "\033[1m" ANSI_COLOR_CYAN "", 10);
}

int	main(int argc, char **argv, char **env)
{
	char	**new_env;
	char	*line;
	t_env	*env_main;
	t_env	*ptr;

	error_code_dollar = 0;
	env_main = ft_create_env(env);
	new_env = rewrite_env_parse(env_main);
	ptr = env_main;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_slash);
	write(1, "\033[1m" ANSI_COLOR_CYAN "", 10);
	line = readline("Minishell-2.🔞 ⌲ ");
	while (line)
	{
		process_the_line(line, &new_env, env_main);
		line = readline("Minishell-2.🔞 ⌲ ");
	}
	ctrl_d();
	while (ptr)
		ptr = free_t_env(ptr);
	free_array((void **)new_env);
	return (error_code_dollar);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:21:27 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/30 19:06:38 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./kshanti/includes_parser/parser.h"

int		main(int argc, char **argv, char **env)
{
	char	**new_env;
	char	*line;
	t_env	*env_main;
	t_env	*ptr;
	
	error_code_dollar = 0;
	env_main = ft_create_env(env);
	new_env = rewrite_env_parse(env_main);
	ptr = env_main;
	write(1, "\033[1m" ANSI_COLOR_CYAN "", 10);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_slash);
	while ((line = readline("Minishell-2.🔞 ⌲ ")))
	{
		if (line && *line)
			add_history(line);
		write(1, "\033[0m" ANSI_COLOR_GREEN "", 10);
		parser(line, &new_env, env_main);
		write(1, "\033[1m" ANSI_COLOR_CYAN "", 10);
	}
	ctrl_d();//exit build in
	while (ptr)
		ptr = free_t_env(ptr);
	free_array((void **)new_env);
	return (0);
}

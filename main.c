/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:21:27 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/01 19:28:18 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./kshanti/includes_parser/parser.h"

int		main(int argc, char **argv, char **env)
{
	t_env	*env_main;
	int		c_env;
	
	env_main = ft_create_env(env, &c_env);
	
	return (0);
}
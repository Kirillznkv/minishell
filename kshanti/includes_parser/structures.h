/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:22:18 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/27 21:14:13 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct			s_commands
{
	int					argc;
	char				*name;
	char				**argv;
	struct s_commands	*next;
}						t_commands;

#endif
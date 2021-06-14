/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:22:18 by kshanti           #+#    #+#             */
/*   Updated: 2021/06/14 21:20:32 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct			s_commands
{
	int					pipe;
	int					fd_flag;
	int					fd_out;
	int					fd_in;
	int					argc;
	char				*name;
	char				**argv;
	int					*delete_fd;
	struct s_commands	*next;
}						t_commands;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:22:18 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/01 19:46:09 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_commands
{
	int					pipe;
	int					fd_flag;
	int					fd_out;
	int					fd_in;
	char				*fd_in_name;
	int					argc;
	char				*name;
	char				**argv;
	int					*delete_fd;
	int					colun_del_fd;
	struct s_commands	*next;
}						t_commands;

#endif
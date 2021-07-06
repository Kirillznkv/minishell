/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 18:53:13 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/06 16:51:16 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

int	is_bash_name(t_commands *command, char *name)
{
	int		i;

	if (!command->name || command->argv[1])
		return (0);
	i = 0;
	if (ft_strlen(command->name) > ft_strlen(name))
		i = ft_strlen(command->name) - ft_strlen(name);
	if (!ft_strncmp(&((command->name)[i]), name, ft_strlen(name)))
	{
		if (i > 0 && (command->name)[i - 1] != '/')
			return (0);
		return (1);
	}
	return (0);
}

int	is_bash(t_commands *command)
{
	if (is_bash_name(command, "minishell"))
		return (1);
	return (0);
}

void	replace_shlvl(t_env *tmp, t_env *env, int value)
{
	if (tmp)
	{
		free(tmp->content->value);
		tmp->content->value = ft_itoa(value);
	}
	else
		add_elem_env(env, new_elem_env(), write_env, "SHLVL=1");
}

void	inc_shlvl(t_env *env)
{
	t_env	*tmp;

	tmp = check_export_line(env, "SHLVL");
	if (tmp)
		replace_shlvl(tmp, env, ft_atoi(tmp->content->value) + 1);
	else
		replace_shlvl(tmp, env, 1);
}

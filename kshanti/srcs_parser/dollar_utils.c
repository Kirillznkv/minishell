/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:52:01 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/05 23:45:01 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

void	no_dollar_word(char **p_c_l, size_t i, size_t j)
{
	int		k;
	char	*s;

	replace_dollar_word(p_c_l, "", (int)i, (int)j);
	s = *p_c_l;
	k = (int)i;
	k--;
	if (k < 0 || s[k] == ' ' || s[k] == '\t' || s[k] == ';' || s[k] == '|')
		skip_spases_tabs(p_c_l, ++k);
}

int	check_env_word(char *env_line, char *dollar_word)
{
	if (env_line[ft_strlen(dollar_word)] == '=')
		return (1);
	return (0);
}

char	*get_second_env_word(char *env_line)
{
	size_t	i;
	char	*second_env_word;

	i = 0;
	while (env_line[i] != '=')
		i++;
	second_env_word = ft_substr(env_line, i + 1, -1);
	return (second_env_word);
}

char	*get_new_dollar_word(char **env, char *dollar_word)
{
	char	*new_dollar_word;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], dollar_word, ft_strlen(dollar_word)) && \
			check_env_word(env[i], dollar_word))
		{
			new_dollar_word = get_second_env_word(env[i]);
			return (new_dollar_word);
		}
		i++;
	}
	return (NULL);
}

void	replace_dollar_word(char **p_command_line, char *new_dollar_word, \
								int beg_dollar, int end_dollar_word)
{
	char	*first_part;
	char	*last_part;
	char	*save_to_free;

	first_part = ft_substr(*p_command_line, 0, beg_dollar);
	last_part = ft_substr(*p_command_line, end_dollar_word, -1);
	free(*p_command_line);
	*p_command_line = ft_strjoin(first_part, new_dollar_word);
	save_to_free = *p_command_line;
	*p_command_line = ft_strjoin(*p_command_line, last_part);
	free(save_to_free);
	free(first_part);
	free(last_part);
}

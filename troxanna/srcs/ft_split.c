/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:02:50 by troxanna          #+#    #+#             */
/*   Updated: 2020/11/17 20:21:24 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	*ft_split_free(char **str_main)
{
	int			i;

	i = 0;
	while (str_main[i])
	{
		free(str_main[i]);
		i++;
	}
	free(str_main);
	return (NULL);
}

static char	**ft_split_malloc_char(char *s, char c, char **str_main)
{
	int			start;
	int			i;
	int			j;

	i = 0;
	j = 0;
	start = 0;
	while (s[j])
	{
		while (s[j] == c && s[j])
			j++;
		if (s[j] != c && s[j])
		{
			start = j;
			while (s[j] != c && s[j])
				j++;
			str_main[i] = ft_substr(s, start, j - start);
			if (!str_main[i])
				return (ft_split_free(str_main));
			i++;
		}
	}
	if (str_main)
		return (str_main);
	return (NULL);
}

static char	**ft_split_string_null(int count)
{
	char	**str_main;

	str_main = (char **)malloc(count * sizeof(char *));
	if (str_main)
	{
		str_main[count - 1] = NULL;
		return (str_main);
	}
	return (NULL);
}

static char	**ft_split_malloc_string(char *s, char c)
{
	char		**str_main;
	int			i;
	int			count;

	i = 0;
	count = 1;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c && s[i])
				i++;
			count++;
		}
		else
			i++;
	}
	if ((i > 0 && s[i - 1] == c) || !ft_strlen(s))
		count--;
	str_main = ft_split_string_null(count + 1);
	if (str_main)
		return (str_main);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	char		**s_main;

	if (!s)
		return (NULL);
	s_main = ft_split_malloc_string(s, c);
	if (s_main)
		return (ft_split_malloc_char(s, c, s_main));
	else
		return (NULL);
}

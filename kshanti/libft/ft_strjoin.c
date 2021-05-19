/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:58:57 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/19 19:41:40 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	// size_t	i;
	// size_t	j;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char*)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	//printf("s1 = |%s| s2 = |%s|\nnew_size = |%zu|\n", s1, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str)
	{
		// i = -1;
		// while (s1[++i])
		// 	str[i] = s1[i];
		// j = -1;
		// while (s2[++j])
		// 	str[i++] = s2[j];
		ft_strlcat(str, s1, ft_strlen(s1) + 1);
		ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	}
	//printf("$|%s|$\n", str);
	return (str);
}

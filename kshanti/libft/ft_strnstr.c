/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:49:10 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/01 19:19:53 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *find, size_t slen)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (find[i] == '\0')
		return ((char *)s);
	if (slen > ft_strlen(s))
		slen = ft_strlen(s);
	while (i < slen && s[i])
	{
		j = 0;
		while (find[j] && s[i + j] && s[i + j] == find[j] && (i + j) < slen)
			j++;
		if (find[j] == '\0')
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

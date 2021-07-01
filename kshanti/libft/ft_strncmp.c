/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:53:25 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/01 19:09:35 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)str1;
	p2 = (unsigned char *)str2;
	i = 0;
	if (num == 0)
	{
		while ((p1[i] || p2[i]) && p1[i] == p2[i])
			i++;
	}
	else
	{
		while ((p1[i] || p2[i]) && i < num - 1 && p1[i] == p2[i])
			i++;
	}
	return (p1[i] - p2[i]);
}

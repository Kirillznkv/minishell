/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:48:34 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/01 19:15:43 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_finder(int n)
{
	unsigned int	ln;
	int				res;

	ln = 0;
	res = 0;
	if (n < 0)
		res++;
	if (n > 0)
		ln = n;
	else
		ln = -n;
	if (n == 0)
		res++;
	while (ln > 0)
	{
		ln /= 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	unsigned int	ln;
	int				size;
	char			*str;

	ln = 0;
	size = size_finder(n);
	str = (char *)ft_calloc(size + 1, sizeof(char));
	if (str)
	{
		if (n == 0)
			str[0] = '0';
		if (n < 0)
			str[0] = '-';
		if (n > 0)
			ln = n;
		else
			ln = -n;
		while (ln > 0)
		{
			str[--size] = ln % 10 + '0';
			ln /= 10;
		}
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:34:21 by glecler           #+#    #+#             */
/*   Updated: 2018/11/15 02:28:07 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	int n;

	n = 0;
	if (src < dst)
	{
		while (n < (int)len)
		{
			((unsigned char *)dst)[len - n - 1] = \
			((unsigned char *)src)[len - n - 1];
			n++;
		}
	}
	else
	{
		while (n < (int)len)
		{
			((unsigned char *)dst)[n] = ((unsigned char *)src)[n];
			n++;
		}
	}
	return (dst);
}

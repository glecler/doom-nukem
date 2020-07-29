/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 01:04:27 by glecler           #+#    #+#             */
/*   Updated: 2018/11/15 01:47:35 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int x;

	x = 0;
	while (x < (int)n)
	{
		if (((unsigned char*)s)[x] == (unsigned char)c)
			return ((unsigned char*)s + x);
		x++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 21:40:11 by glecler           #+#    #+#             */
/*   Updated: 2018/11/19 20:43:39 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t x;
	size_t y;
	size_t z;

	z = ft_strlen(dst);
	y = ft_strlen(src);
	x = z;
	while (*src && z + 1 < size)
		dst[z++] = *(src++);
	dst[z] = 0;
	return (y + ((x > size) ? size : x));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 02:01:00 by glecler           #+#    #+#             */
/*   Updated: 2018/11/15 02:23:08 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int x;

	x = 0;
	while (x < (int)n && ((unsigned char*)s1)[x] == ((unsigned char*)s2)[x])
		x++;
	if (x < (int)n)
		return (((unsigned char*)s1)[x] - ((unsigned char*)s2)[x]);
	return (0);
}

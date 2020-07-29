/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 03:46:21 by glecler           #+#    #+#             */
/*   Updated: 2018/11/15 21:22:02 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		x;
	int		i;

	x = 0;
	i = (int)ft_strlen(s1);
	if (!(s2 = malloc(sizeof(*s1) * i + 1)))
		return (0);
	while (x < i)
	{
		s2[x] = s1[x];
		x++;
	}
	s2[x] = '\0';
	return (s2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:45:09 by glecler           #+#    #+#             */
/*   Updated: 2018/12/04 12:46:36 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	x;
	size_t	y;
	char	*str;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	x = ft_strlen(s1);
	y = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(*str) * (x + y + 1))))
		return (NULL);
	while (++i < x)
		str[i] = s1[i];
	i = -1;
	while (++i < y)
		str[i + x] = s2[i];
	str[x + y] = '\0';
	return (str);
}

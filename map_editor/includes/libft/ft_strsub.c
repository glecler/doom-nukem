/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:36:34 by glecler           #+#    #+#             */
/*   Updated: 2018/12/04 12:00:58 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(*str) * ((int)len + 1))))
		return (NULL);
	while (i < (unsigned int)len)
	{
		str[i] = s[start + (unsigned int)i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

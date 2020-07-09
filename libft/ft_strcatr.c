/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcatr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by ravernhe          #+#    #+#             */
/*   Updated: 2019/11/30 17:30:31 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strcatr(char *dest, const char *src)
{
	int 	i;
	int 	j;
	char	*cpy;

	j = -1;
	i = -1;
	cpy = ft_strdup(dest);
	while (src[++i])
		dest[i] = src[i];
	while (cpy[++j])
		dest[j + i] = cpy[j];
	dest[j + i] = '\0';
	free(cpy);
	return (dest);
}

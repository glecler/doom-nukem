/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_treatment_percent.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 06:37:29 by glecler           #+#    #+#             */
/*   Updated: 2019/10/30 06:38:02 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_percent(t_flags flags)
{
	char	*buff;
	int		mallocsize;
	int		i;
	char	c;

	i = 0;
	c = (flags.zero > 0 ? '0' : ' ');
	mallocsize = (flags.width > 1 ? flags.width : 1);
	if (!(buff = ft_strnew_gr(mallocsize)))
		return (NULL);
	if (flags.minus > 0)
	{
		buff[i++] = '%';
		while (flags.width-- > 1)
			buff[i++] = c;
	}
	else
	{
		while (flags.width-- > 1)
			buff[i++] = c;
		buff[i++] = '%';
	}
	return (buff);
}

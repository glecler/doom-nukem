/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_treatment_oxx.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 09:10:11 by glecler           #+#    #+#             */
/*   Updated: 2019/11/03 14:08:52 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int			ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_oxx(t_flags flags, char *nb, char type)
{
	int		len;
	int		ms;
	char	*buff;

	buff = NULL;
	flags.hash = (*nb == '0' && type != 'p' ? 0 : flags.hash);
	if (*nb == '0' && flags.precision == 0 && flags.dot == 1 && type != 'p')
		nb = ft_zero(nb);
	len = ft_strlen(nb);
	flags.hash = hash_diff(type, len, flags.precision, flags.hash);
	flags.hash = (type == 'p' ? 2 : flags.hash);
	len += (flags.hash > 0) + (flags.hash > 1);
	ms = ((flags.width > len && flags.width
			> flags.precision) ? flags.width : len);
	ms = (flags.precision + (flags.hash > 0) + (flags.hash > 1) >
		ms ? flags.precision + (flags.hash > 0) + (flags.hash > 1) : ms);
	if (!(buff = ft_strnew_gr(ms)))
		return (NULL);
	if (flags.minus == 0)
		buff = ft_minus_0_oxx(flags, nb, buff, len);
	else
		buff = ft_minus_1_oxx(flags, nb, buff, len);
	free(nb);
	return (buff);
}

char	*ft_0_oxx_one(t_flags flags, char *nb, char *buff, int len)
{
	int		i;
	char	c;

	i = 0;
	c = ((flags.zero > 0 && flags.dot == 0) ? '0' : ' ');
	if (flags.hash != 0 && (flags.hash != 1 ||
		(flags.hash == 1 && flags.precision < len)))
		buff[i++] = '0';
	flags.hash == 2 ? buff[i++] = 'x' : 0;
	flags.hash == 3 ? buff[i++] = 'X' : 0;
	while (flags.width > len && flags.width > (flags.precision
			+ (flags.hash > 0) + (flags.hash > 1)))
	{
		flags.width--;
		buff[i++] = c;
	}
	while ((flags.precision-- > len - (flags.hash > 0) - (flags.hash > 1)))
		buff[i++] = '0';
	while (*nb && buff[i])
		buff[i++] = *(nb++);
	return (buff);
}

char	*ft_0_oxx_two(t_flags flags, char *nb, char *buff, int len)
{
	int		i;
	char	c;

	i = 0;
	c = ((flags.zero > 0 && flags.dot == 0) ? '0' : ' ');
	while (flags.width > len && flags.width > (flags.precision
			+ (flags.hash > 0) + (flags.hash > 1)))
	{
		flags.width--;
		buff[i++] = c;
	}
	if ((flags.hash > 0))
	{
		if (flags.hash != 1 || (flags.hash == 1 && flags.precision < len))
			buff[i++] = '0';
		flags.hash == 2 ? buff[i++] = 'x' : 0;
		flags.hash == 3 ? buff[i++] = 'X' : 0;
	}
	while ((flags.precision-- > len - (flags.hash > 0) - (flags.hash > 1)))
		buff[i++] = '0';
	while (*nb && buff[i])
		buff[i++] = *(nb++);
	return (buff);
}

char	*ft_minus_1_oxx(t_flags flags, char *nb, char *buff, int len)
{
	int	i;
	int prec;

	i = 0;
	prec = flags.precision;
	if (flags.hash >= 1)
		buff[i++] = '0';
	if (flags.hash == 2)
		buff[i++] = 'x';
	if (flags.hash == 3)
		buff[i++] = 'X';
	while ((prec-- + (flags.hash > 0) + (flags.hash > 1))
			> len && buff[i])
		buff[i++] = '0';
	while (*nb)
		buff[i++] = *(nb++);
	while (flags.width > len && flags.width > flags.precision && buff[i])
	{
		flags.width--;
		buff[i++] = ' ';
	}
	buff[i] = '\0';
	return (buff);
}

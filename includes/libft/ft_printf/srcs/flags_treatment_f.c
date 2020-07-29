/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_treatment_f.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:56:11 by glecler           #+#    #+#             */
/*   Updated: 2019/10/30 06:36:12 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_f_nb(t_flags flags, va_list ap)
{
	if (flags.dot == 0 && flags.precision == 0)
		flags.precision = 6;
	if (flags.l == 1)
		return (ftoa(va_arg(ap, double), 0, flags.precision));
	if (flags.bigl == 1)
		return (ftoa(va_arg(ap, long double), 0, flags.precision));
	return (ftoa(va_arg(ap, double), 0, flags.precision));
}

char	*ft_floats(char *nb, t_flags flags)
{
	char	*buff;
	int		mallocsize;
	int		len;

	buff = NULL;
	if (!(nb))
		return (NULL);
	if (*nb == '-')
		flags = minus_flags(flags);
	if (flags.dot == 0 && flags.precision == 0)
		flags.precision = 6;
	len = ft_strlen(nb) + (flags.hash > 0 && flags.precision == 0)
		+ (flags.plus > 0);
	mallocsize = (flags.width > len ? flags.width : len);
	if (!(buff = ft_strnew_gr(mallocsize)))
		return (NULL);
	if (flags.minus == 0)
		buff = ft_minus_0_f(flags, nb, buff, len);
	else
		buff = ft_minus_1_f(flags, nb, buff, len);
	free(nb);
	return (buff);
}

char	*ft_minus_0_f(t_flags flags, char *nb, char *buff, long len)
{
	int		i;
	char	c;

	i = 0;
	if (flags.space > 0 && *nb != '-')
		buff[i++] = ' ';
	c = (flags.zero > 0 && flags.minus == 0 ? '0' : ' ');
	if (*nb == '-' && flags.zero > 0)
		buff[i++] = *(nb++);
	while (flags.width > len + (flags.space > 0))
	{
		flags.width--;
		buff[i++] = c;
	}
	*nb == '-' && flags.zero == 0 ? buff[i++] = *(nb++) : 0;
	if (flags.zero == 0 && flags.plus == 1)
		buff[i++] = (*nb == '-' ? '-' : '+');
	nb = (*nb == '-' && flags.plus > 0 ? nb + 1 : nb);
	while (buff[i] && *nb)
		buff[i++] = *(nb++);
	if (flags.hash > 0 && strchr2('.', nb - i) == 0)
		buff[i++] = '.';
	return (buff);
}

char	*ft_minus_1_f(t_flags flags, char *nb, char *buff, long len)
{
	int i;

	i = 0;
	if (flags.space > 0 && *nb != '-')
		buff[i++] = ' ';
	if (flags.plus > 0 && *nb != '-')
		buff[i++] = '+';
	if (*nb == '-')
	{
		buff[i++] = '-';
		nb++;
	}
	while (*nb)
		buff[i++] = *(nb++);
	if (flags.hash > 0 && strchr2('.', nb) == 0)
		buff[i++] = '.';
	while (flags.width > len + (flags.space > 0))
	{
		flags.width--;
		buff[i++] = ' ';
	}
	return (buff);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_treatment_diu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:33:28 by glecler           #+#    #+#             */
/*   Updated: 2019/11/03 14:08:29 by glecler          ###   ########.fr       */
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

char	*ft_zero(char *str)
{
	free(str);
	if (!(str = ft_strnew_gr(0)))
		return (0);
	return (str);
}

char	*ft_di(t_flags flags, char *nb)
{
	long	len;
	long	mallocsize;
	char	*buff;

	if (*nb == '-')
		flags = minus_flags(flags);
	if (flags.zero > 0 && flags.precision > 0)
		flags.zero = 0;
	if (*nb == '0' && flags.precision == 0 && flags.dot == 1)
		nb = ft_zero(nb);
	len = (flags.plus > 0) + (ft_strlen(nb)) + (flags.space > 0);
	mallocsize = (flags.width > len && flags.width >
			flags.precision ? flags.width : len);
	mallocsize = (flags.precision + flags.space + flags.plus +
		flags.signe > mallocsize ? flags.precision +
			flags.signe + (flags.space > 0) + flags.plus : mallocsize);
	if (!(buff = ft_strnew_gr(mallocsize)))
		return (NULL);
	if (flags.minus == 0)
		buff = ft_minus_0(flags, nb, buff, len);
	else
		buff = ft_minus_1(flags, nb, buff, len);
	free(nb);
	return (buff);
}

char	*ft_minus_0(t_flags flags, char *nb, char *buff, long len)
{
	int		i;
	char	c;

	i = 0;
	if (flags.space > 0 && *nb != '-')
		buff[i++] = ' ';
	c = (flags.zero > 0 && flags.dot == 0 ? '0' : ' ');
	if (flags.plus > 0 && flags.zero > 0 && flags.signe == 0)
		buff[i++] = '+';
	if (*nb == '-' && flags.zero > 0 && flags.dot == 0)
		buff[i++] = *(nb++);
	while ((flags.width > len && flags.width-- >
			flags.precision + (flags.plus > 0) + flags.signe + flags.space))
		buff[i++] = c;
	*nb == '-' && flags.zero == 0 ? buff[i++] = *(nb++) : 0;
	if (flags.plus > 0 && flags.zero == 0)
		buff[i++] = (*nb == '-' ? '-' : '+');
	nb = (*nb == '-' && flags.plus > 0 ? nb + 1 : nb);
	while (flags.precision-- > len - (flags.plus > 0) -
		(flags.space > 0) - flags.signe)
		buff[i++] = '0';
	while (buff[i] && *nb)
		buff[i++] = *(nb++);
	return (buff);
}

char	*ft_minus_1(t_flags flags, char *nb, char *buff, long len)
{
	int i;
	int prec;

	prec = flags.precision;
	i = 0;
	if (flags.space > 0 && *nb != '-')
		buff[i++] = ' ';
	if (flags.plus > 0 && *nb != '-')
		buff[i++] = '+';
	if (*nb == '-')
		buff[i++] = *(nb++);
	while (prec-- + flags.signe + flags.plus + flags.space > len)
		buff[i++] = '0';
	while (*nb && buff[i])
		buff[i++] = *(nb++);
	while (buff[i] != 0 && flags.width > len && flags.width >
			flags.precision + flags.plus + flags.space - flags.signe)
	{
		flags.width--;
		buff[i++] = ' ';
	}
	buff[i] = 0;
	return (buff);
}

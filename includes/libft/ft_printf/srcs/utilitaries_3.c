/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitaries_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:26:42 by glecler           #+#    #+#             */
/*   Updated: 2019/10/19 13:01:14 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			f_get_nb(long double nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		nb = -1.0 * nb;
		i++;
	}
	if (nb < 1)
		return (1);
	while (nb >= 1)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

long double	part_ent(long double d)
{
	long double	part_en;
	int			x;
	int			i;

	i = f_get_nb(d);
	part_en = 0;
	while (i > 0)
	{
		x = d / f_ft_pow(10, i - 1);
		d = d - (x * f_ft_pow(10, i - 1));
		part_en = part_en + x * f_ft_pow(10, i - 1);
		i--;
	}
	return (part_en);
}

char		*i_ftoa(long double n, int i, char *nb, int precision)
{
	long double	ncpy;
	int			x;

	ncpy = n;
	x = 0;
	if (part_ent(n) == 0)
		nb[i++] = '0';
	while (ncpy >= 1)
	{
		ncpy = ncpy / 10;
		x++;
	}
	if ((i > 0 && nb[0] != '-') || (i > 1 && nb[0] == '-'))
		x = (precision > x ? precision : x);
	while (x > 0 && nb[i])
	{
		nb[i] = (part_ent(n / ft_pow(10, x - 1)) + 48);
		n = n - ((nb[i] - 48) * ft_pow(10, x - 1));
		x--;
		i++;
	}
	return (nb);
}

char		*ftoa(long double n, int i, int precision)
{
	char		*nb;
	long double	dec;

	nb = NULL;
	if (!(nb = ft_strnew_gr(f_get_nb(n) + precision + (precision != 0))))
		return (NULL);
	if (n < 0)
	{
		n = -1 * n;
		nb[i++] = '-';
	}
	dec = part_ent((((n - part_ent(n)) * ft_pow(10, precision + 1))) / 10);
	if (((n * f_ft_pow(10, precision + 1)) - (part_ent(n *
		f_ft_pow(10, precision)) * 10)) >= 5 && precision > 0)
		dec += 1;
	if (((n * f_ft_pow(10, precision + 1)) - (part_ent(n *
		f_ft_pow(10, precision)) * 10)) >= 5 && precision == 0)
		n += 1;
	nb = i_ftoa(part_ent(n), i, nb, precision);
	i += f_get_nb(part_ent(n));
	if (precision != 0)
		nb[i] = '.';
	nb = i_ftoa(dec, i + 1, nb, precision);
	return (nb);
}

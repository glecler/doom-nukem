/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitaries.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 14:03:28 by glecler           #+#    #+#             */
/*   Updated: 2019/10/19 12:55:46 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_strnew_gr(long i)
{
	char	*str;
	int		x;

	x = -1;
	if (!(str = (char*)malloc((char)(i + 1))))
		exit(0);
	while (++x < i)
		str[x] = '0';
	str[i] = '\0';
	return (str);
}

int				get_nb(long long int nb, int base)
{
	int i;

	i = 0;
	if (nb < 0)
	{
		i++;
		nb = -1 * nb;
	}
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb = nb / base;
		i++;
	}
	return (i);
}

int				u_get_nb(unsigned long long int nb, int base)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb = nb / base;
		i++;
	}
	return (i);
}

char			*u_ltoa(unsigned long long int n, char type, int x, int i)
{
	unsigned int	base;
	char			*nb;

	type == 'u' ? base = 10 : 0;
	type == 'o' ? base = 8 : 0;
	(type == 'x' || type == 'X') ? base = 16 : 0;
	if (!(nb = ft_strnew_gr(u_get_nb(n, base))))
		return (NULL);
	while ((n / ft_pow(base, x) >= base))
		x++;
	while (x >= 0)
	{
		if (base > 10 && (n / ft_pow(base, x) >= 10))
			nb[i] = n / ft_pow(base, x) + (type == 'x' ? 87 : 55);
		else
			nb[i] = (n / ft_pow(base, x) + 48);
		n = (n % ft_pow(base, x));
		x--;
		i++;
	}
	return (nb);
}

char			*ltoa(long long int n, int x, int i)
{
	char	*nb;

	if (!(nb = ft_strnew_gr(get_nb(n, 10))))
		return (NULL);
	if (n < 0)
	{
		n = -1 * n;
		nb[i++] = '-';
	}
	while ((n / ft_pow(10, x) >= 10))
		x++;
	while (x >= 0)
	{
		nb[i] = (n / ft_pow(10, x) + 48);
		n = (n % ft_pow(10, x));
		x--;
		i++;
	}
	return (nb);
}

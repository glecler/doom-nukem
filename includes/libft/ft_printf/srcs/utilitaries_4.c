/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitaries_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:54:45 by glecler           #+#    #+#             */
/*   Updated: 2019/10/30 06:41:44 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

double	f_ft_pow(int base, int x)
{
	if (x != 0)
		return (base * ft_pow(base, x - 1));
	else
		return (1);
}

int		get_nb_digit(const char *str)
{
	int i;

	i = 0;
	while (str[i] != 0 && str[i] >= '0' && str[i] <= '9')
		i++;
	return (i);
}

int		hash_diff(char type, int len, int prec, int hash)
{
	if (hash == 0)
		return (0);
	if (type == 'o' && prec > len)
		return (0);
	if (type == 'x')
		return (2);
	if (type == 'X')
		return (3);
	return (1);
}

char	*ft_easier(char c)
{
	char *str;

	if (!(str = ft_strnew_gr(1)))
		return (NULL);
	*str = c;
	return (str);
}

char	*ft_minus_0_oxx(t_flags flags, char *nb, char *buff, int len)
{
	int		i;

	i = 0;
	if (flags.dot == 1)
		flags.zero = 0;
	if ((flags.width > (flags.precision
			+ (flags.hash > 0) + (flags.hash > 1)) && flags.zero > 0))
		return (ft_0_oxx_one(flags, nb, buff, len));
	else
		return (ft_0_oxx_two(flags, nb, buff, len));
}
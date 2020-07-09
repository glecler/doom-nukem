/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by ravernhe          #+#    #+#             */
/*   Updated: 2019/11/30 17:28:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	*ft_execp(int n)
{
	if (n == 0)
		return (ft_strdup("0"));
	return (ft_strdup("-2147483648"));
}

static char	*ft_int_to_str(int i, int nb, int neg, char *str)
{
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	i--;
	while (nb > 0)
	{
		str[i] = (nb % 10) + '0';
		nb = nb / 10;
		i--;
	}
	if (neg == 1)
		str[0] = '-';
	return (str);
}

char		*ft_itoa(int n)
{
	int		i;
	int		nb;
	int		neg;
	char	*str;

	str = NULL;
	i = 0;
	neg = 0;
	if (n == -2147483648 || n == 0)
		return (ft_execp(n));
	if (n < 0)
	{
		n = n * -1;
		neg = 1;
		i++;
	}
	nb = n;
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	str = ft_int_to_str(i, nb, neg, str);
	return (str);
}

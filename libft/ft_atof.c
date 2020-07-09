/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/03 09:58:48 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	mantis(double *a, const char *s, int *c, int *e)
{
	while ((*c = *s++) != '\0' && ft_isdigit(*c))
		*a = *a * 10.0 + (*c - '0');
	if (*c == '.')
	{
		while ((*c = *s++) != '\0' && ft_isdigit(*c))
		{
			*a = *a * 10.0 + (*c - '0');
			*e -= 1;
		}
	}
}

void	adjust(double *a, int e)
{
	while (e > 0)
	{
		*a *= 10.0;
		e--;
	}
	while (e < 0)
	{
		*a *= 0.1;
		e++;
	}
}

double	ft_atof(const char *s)
{
	double	a;
	int		e;
	int		c;
	int		sign;

	sign = 1;
	a = 0.0;
	e = 0;
	while ((c = *s++) != '\0' && c <= 32)
		sign = 1;
	if (c == '-')
		sign = -1;
	else
		c = *s--;
	mantis(&a, s, &c, &e);
	adjust(&a, e);
	a *= sign;
	return (a);
}

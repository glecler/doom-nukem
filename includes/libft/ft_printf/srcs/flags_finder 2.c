/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 12:36:47 by glecler           #+#    #+#             */
/*   Updated: 2019/10/30 06:39:00 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_flags(t_flags *flags)
{
	flags->hh = 0;
	flags->h = 0;
	flags->ll = 0;
	flags->l = 0;
	flags->z = 0;
	flags->j = 0;
	flags->bigl = 0;
	flags->hash = 0;
	flags->zero = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->dot = 0;
	flags->i = 0;
	flags->signe = 0;
	flags->type = 0;
}

/*
** gets flags #+- ", i, precision, width
*/

t_flags	ft_get_flags(const char *restrict format, t_flags flags)
{
	ft_init_flags(&flags);
	while (*format && strchr2(*format, "#+0- ") == 1)
	{
		flags.hash += (*format == '#' ? 1 : 0);
		flags.zero += (*format == '0' ? 1 : 0);
		flags.minus += (*format == '-' ? 1 : 0);
		flags.plus += (*format == '+' ? 1 : 0);
		flags.space += (*format == ' ' ? 1 : 0);
		format++;
	}
	flags.i += flags.hash + flags.zero + flags.minus + flags.plus + flags.space;
	flags.width = ft_get_width(format);
	flags.i += get_nb_digit(format);
	format += get_nb_digit(format);
	*format == '.' ? flags.dot = 1 : 0;
	flags.precision = ft_get_precision(format);
	flags.i += get_nb_digit(format + flags.dot) + flags.dot;
	return (flags);
}

/*
** gets lenght specifiers l ll h hh
*/

t_flags	ft_get_ls(const char *format, t_flags flags)
{
	flags.i = 0;
	while (*format && strchr2(*format, "hlLjz") == 1)
	{
		if (*format == 'h' && *(format + 1) == 'h')
			flags.hh += 1;
		if (*format == 'h' && flags.hh == 0)
			flags.h += 1;
		if (*format == 'l' && *(format + 1) == 'l')
			flags.ll += 1;
		if (*format == 'l' && flags.ll == 0)
			flags.l += 1;
		if (*format == 'L')
			flags.bigl += 1;
		if (*format == 'j')
			flags.j += 1;
		if (*format == 'z')
			flags.z += 1;
		flags.i++;
		format++;
	}
	return (flags);
}

int		ft_get_width(const char *format)
{
	int temp;

	temp = 0;
	while (*format >= '0' && *format <= '9')
	{
		temp = (temp * 10) + (*format - '0');
		format++;
	}
	return (temp);
}

int		ft_get_precision(const char *format)
{
	int temp;

	temp = 0;
	if (*format == '.')
	{
		format++;
		while (*format >= '0' && *format <= '9')
		{
			temp = (temp * 10) + (*format - '0');
			format++;
		}
	}
	return (temp);
}

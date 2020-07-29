/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:43:32 by glecler           #+#    #+#             */
/*   Updated: 2019/10/19 12:53:20 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int ft_putchar(char c)
{
	if (!(write(1, &c, 1)))
		return(0);
	return (1);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	int			ret;

	ret = 0;
	va_start(ap, format);
	ret = ft_read(format, ap, ret);
	va_end(ap);
	return (ret);
}

int		ft_read(const char *restrict format, va_list ap, int ret)
{
	char	*buff;

	while (*format)
	{
		if (*format != '%')
			ret += ft_putchar(*format);
		if (*format == '%')
		{
			if (!(buff = ft_fetch(format, ap)))
				return (-1);
			ret += ft_putstr_gr(buff, format);
			free(buff);
			format = ft_end(format) - 1;
		}
		format++;
	}
	return (ret);
}

char	*ft_fetch(const char *restrict format, va_list ap)
{
	t_flags		flags;
	char		type;

	ft_init_flags(&flags);
	flags = ft_get_flags(format + 1, flags);
	format += flags.i + 1;
	flags = ft_get_ls(format, flags);
	format += flags.i;
	type = *format;
	flags.type = *format;
	return (ft_treat(flags, type, ap));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_ls_treatment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:23:01 by glecler           #+#    #+#             */
/*   Updated: 2019/11/03 14:09:02 by glecler          ###   ########.fr       */
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

static char	*ft_strdup(char *str)
{
	char	*str_dup;
	int		i;

	i = 0;
	if (!(str))
		return (NULL);
	if (!(str_dup = ft_strnew_gr(ft_strlen(str))))
		return (NULL);
	while (str[i])
	{
		str_dup[i] = str[i];
		i++;
	}
	return (str_dup);
}

char	*ft_treat(t_flags flags, char type, va_list ap)
{
	flags = flags_comp(flags, type);
	if (strchr2(type, "di") == 1)
		return (ft_di(flags, ft_di_nb(flags, ap)));
	if (strchr2(type, "oxX") == 1)
		return (ft_oxx(flags, ft_ouxx_nb(flags, ap, type), type));
	if (strchr2(type, "u") == 1)
		return (ft_di(flags, ft_ouxx_nb(flags, ap, type)));
	if (type == 'c')
		return (ft_s(ft_easier(va_arg(ap, int)), flags));
	if (type == 's')
		return (ft_s(ft_strdup(va_arg(ap, char*)), flags));
	if (type == 'p')
		return (ft_oxx(flags, ft_fetch("%llx", ap), type));
	if (type == 'f')
		return (ft_floats(ft_f_nb(flags, ap), flags));
	if (type == '%')
		return (ft_percent(flags));
	return (0);
}

char	*ft_di_nb(t_flags flags, va_list ap)
{
	if (flags.h == 1)
		return (ltoa(((short int)va_arg(ap, int)), 0, 0));
	if (flags.hh == 1)
		return (ltoa((signed char)va_arg(ap, int), 0, 0));
	if (flags.l == 1)
		return (ltoa(va_arg(ap, long int), 0, 0));
	if (flags.ll == 1)
		return (ltoa(va_arg(ap, long long int), 0, 0));
	if (flags.z == 1)
		return (ltoa(va_arg(ap, size_t), 0, 0));
	if (flags.j == 1)
		return (ltoa(va_arg(ap, intmax_t), 0, 0));
	return (ltoa(va_arg(ap, int), 0, 0));
}

char	*ft_ouxx_nb(t_flags flags, va_list ap, char type)
{
	if (flags.h == 1)
		return (u_ltoa((unsigned short int)va_arg(ap, int), type, 0, 0));
	if (flags.hh == 1)
		return (u_ltoa((unsigned char)va_arg(ap, int), type, 0, 0));
	if (flags.l == 1)
		return (u_ltoa(va_arg(ap, unsigned long int), type, 0, 0));
	if (flags.ll == 1)
		return (u_ltoa(va_arg(ap, unsigned long long int), type, 0, 0));
	if (flags.z == 1)
		return (u_ltoa(va_arg(ap, size_t), type, 0, 0));
	if (flags.j == 1)
		return (u_ltoa(va_arg(ap, uintmax_t), type, 0, 0));
	if (type == 'u')
		return (u_ltoa((unsigned)va_arg(ap, unsigned int), type, 0, 0));
	else
		return (u_ltoa((unsigned)va_arg(ap, int), type, 0, 0));
}

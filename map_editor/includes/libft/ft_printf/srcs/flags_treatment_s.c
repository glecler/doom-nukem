/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_treatment_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 18:47:48 by glecler           #+#    #+#             */
/*   Updated: 2019/10/30 05:49:18 by glecler          ###   ########.fr       */
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

char	*ft_minus_1_s(t_flags flags, char *str, char *buff, int len)
{
	int		i;
	char	c;

	i = 0;
	c = (flags.zero == 0 ? ' ' : '0');
	while (len-- > 0)
	{
		buff[i] = str[i];
		i++;
	}
	while (flags.width - i > 0)
		buff[i++] = c;
	return (buff);
}

char	*ft_minus_0_s(t_flags flags, char *str, char *buff, int len)
{
	int		i;
	char	c;

	i = 0;
	c = (flags.zero == 0 ? ' ' : '0');
	while ((flags.width--) - len > 0 && buff[i])
		buff[i++] = c;
	while (len-- > 0 && buff[i])
	{
		buff[i] = *(str++);
		i++;
	}
	return (buff);
}

char	*ft_s(char *str, t_flags flags)
{
	char	*buff;
	int		mallocsize;
	int		len;

	buff = NULL;
	if (!(str))
		str = ft_strdup("(null)");
	len = (flags.dot > 0 && flags.precision < ft_strlen(str) ?
		flags.precision : ft_strlen(str));
	len = (flags.type == 'c' ? 1 : len);
	mallocsize = (flags.width > len ? flags.width : len);
	if (!(buff = ft_strnew_gr(mallocsize)))
		return (NULL);
	if (flags.minus > 0)
		buff = ft_minus_1_s(flags, str, buff, len);
	else
		buff = ft_minus_0_s(flags, str, buff, len);
	free(str);
	return (buff);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:53:16 by glecler           #+#    #+#             */
/*   Updated: 2018/12/04 12:07:50 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswhitespaces(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

static int	ft_compte(char const *s)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (ft_iswhitespaces(s[i]) == 1)
		i++;
	x = i;
	while (s[i])
		i++;
	while (ft_iswhitespaces(s[--i]) == 1)
		;
	i = i - x;
	if (i <= 0)
		return ((int)ft_strlen(s));
	return (i + 1);
}

char		*ft_strtrim(char const *s)
{
	char	*copy;
	int		x;
	int		i;
	int		j;

	x = 0;
	j = 0;
	if (!s)
		return (NULL);
	i = ft_compte(s);
	if (!(copy = (char *)malloc(sizeof(*s) * (i + 1))))
		return (NULL);
	while (ft_iswhitespaces(s[j]) == 1)
		j++;
	while (x < i)
		copy[x++] = s[j++];
	copy[x] = '\0';
	return (copy);
}

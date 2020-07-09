/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:57:06 by glecler           #+#    #+#             */
/*   Updated: 2018/12/04 14:41:55 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_ischar(char i, char c)
{
	return (i == c ? 1 : 0);
}

static int		ft_nbrcount(char const *s, char c)
{
	int i;
	int compteur;

	i = 0;
	compteur = 0;
	while (s[i] != '\0')
	{
		i = i + ft_ischar(s[i], c);
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != '\0' && s[i] != c)
				i++;
			compteur++;
		}
	}
	return (compteur);
}

static char		**ft_lettercount(char const *s, char c, int compteur, int x)
{
	int		i;
	int		nbr;
	char	**str;

	i = 0;
	nbr = 0;
	if (!(str = (char **)malloc(sizeof(*str) * compteur + 1)))
		return (NULL);
	while (s[i] != '\0')
	{
		i = i + ft_ischar(s[i], c);
		if (s[i] != '\0' && s[i] != c)
		{
			while (s[i] != '\0' && s[i] != c)
			{
				i++;
				nbr++;
			}
			if (!(str[x] = (char *)malloc(sizeof(*str) * (nbr + 1))))
				return (NULL);
			x++;
			nbr = 0;
		}
	}
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		x;
	int		y;
	char	**str;

	i = 0;
	x = 0;
	y = 0;
	if (s == NULL || !(str = ft_lettercount(s, c, ft_nbrcount(s, c), x)))
		return (NULL);
	while (s[i] != '\0')
	{
		i = i + ft_ischar(s[i], c);
		if (s[i] != '\0' && s[i] != c)
		{
			while (s[i] != '\0' && s[i] != c)
				str[x][y++] = s[i++];
			str[x][y] = '\0';
			x++;
			y = 0;
		}
	}
	str[x] = 0;
	return (str);
}

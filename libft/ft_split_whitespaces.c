/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by ravernhe          #+#    #+#             */
/*   Updated: 2019/11/30 17:30:23 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int			count_word(char *str)
{
	int	i;
	int	nb_mots;

	i = 0;
	nb_mots = 0;
	while (str[i])
	{
		while (str[i] > 32 && str[i])
			i++;
		if (str[i - 1] > 32 && str[i - 1])
			nb_mots++;
		while (str[i] <= 32 && str[i])
			i++;
	}
	return (nb_mots);
}

int			c_cha(char *str, int *i)
{
	int	nb_char;

	nb_char = 0;
	while (str[*i] <= 32 && str[*i])
		*i = *i + 1;
	while (str[*i] > 32 && str[*i])
	{
		*i = *i + 1;
		nb_char++;
	}
	return (nb_char);
}

static char	*ft_new_strdup(char *src, int *j)
{
	char	*str;
	int		tmp;
	int		x;

	x = 0;
	while (src[*j] <= 32 && src[*j])
		*j = *j + 1;
	tmp = *j;
	while (src[tmp] > 32 && src[tmp])
		tmp++;
	str = (char *)malloc(sizeof(*str) * (tmp - *j + 1));
	while (src[*j] > 32 && src[*j])
	{
		str[x] = src[*j];
		x++;
		*j = *j + 1;
	}
	str[x] = '\0';
	return (str);
}

char		**ft_split_whitespaces(char *str)
{
	char	**dest;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!(dest = (char **)malloc(sizeof(*dest) * (count_word(str) + 1))))
		return (0);
	while (++i < count_word(str))
		dest[i] = ft_new_strdup(str, &j);
	dest[i] = 0;
	return (dest);
}

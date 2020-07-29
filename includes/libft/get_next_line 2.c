/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:34:16 by glecler           #+#    #+#             */
/*   Updated: 2019/10/28 15:12:10 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find(char *str)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*lecture(char *str, const int fd, int *z, int x)
{
	char	*buff;
	char	*temp;

	x = 0;
	if (!(buff = malloc(GNL_SIZE + 1)))
		return (NULL);
	while ((x = read(fd, buff, GNL_SIZE)) > 0)
	{
		buff[x] = '\0';
		if (!(temp = ((!(str)) ? ft_strdup(buff) : ft_strjoin(str, buff))))
			return (NULL);
		if (str)
			free(str);
		if (!(str = ft_strdup(temp)))
			return (NULL);
		free(temp);
		if (find(buff) == 1)
			break ;
	}
	if (x == 0)
		*z = 1;
	if (x == -1)
		str = NULL;
	free(buff);
	return (str);
}

static char	*save_line(char *str, char **line, int *y)
{
	int		x;
	char	*tmp;

	x = 0;
	if (str[x])
	{
		while (str[x] != '\n' && str[x])
			x++;
		if (x != 0 || (x == 0 && str[x] == '\n'))
		{
			if ((!((*line) = ft_strsub(str, 0, x + 1)))
					|| (!(tmp = ft_strsub(str, x + 1,
								(int)(ft_strlen(str)) - x))))
				return (NULL);
			free(str);
			if (!(str = ft_strdup(tmp)))
				return (NULL);
			free(tmp);
			if (str)
				return (str);
		}
	}
	*y = 1;
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*str;
	int			y;
	int			z;

	y = 0;
	z = 0;
	if (GNL_SIZE < 1 || fd < 0 || !line || !(str = lecture(str, fd, &z, y)))
		return (z == 1 ? 0 : -1);
	if (!(str = save_line(str, line, &y)))
	{
		free(str);
		return (y == 1 ? 0 : -1);
	}
	return (1);
}

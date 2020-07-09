/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser_tools_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:15:06 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_vec2d *vec2_memcpy(t_vec2d *dest, t_vec2d *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

t_vec2d *vec2_add_size(t_vec2d *data, int size)
{
	t_vec2d	*cpy;

	if (!(cpy = malloc(sizeof(t_vec2d) * (4096 * size))))
		exit (0);
	if (size > 1)
		cpy = vec2_memcpy(cpy, data, 4096 * (size - 1));
	free(data);
	return (cpy);
}

t_vec2d		p_vec2(char *str, t_vec2d vec)
{
	int	i;

	i = 0;
	i = skip(str, i);
	vec.u = ft_atof(str + i);
	i = skip(str, i);
	vec.v = ft_atof(str + i);
	vec.w = 1.0f;
	return (vec);
}

t_texture	get_tex_name(char *buff, t_texture tex)
{
	int i;
	int k;

	k = 0;
	i = 7;
	if (!(tex.name = malloc(sizeof(char) * (ft_strlen(buff) + 2))))
		exit(0);
	while (buff[i] != '\n' && buff[i] != '\0')
	{
		tex.name[k] = buff[i];
		i++;
		k++;
	}
	tex.name[k] = '\0';
	return (tex);
}

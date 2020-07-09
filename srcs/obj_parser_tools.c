/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:09:55 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_vec3d *vec_memcpy(t_vec3d *dest, t_vec3d *src, size_t n)
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

t_vec3d *vec_add_size(t_vec3d *data, int size)
{
	t_vec3d	*cpy;

	if (!(cpy = malloc(sizeof(t_vec3d) * (4096 * size))))
		exit (0);
	if (size > 1)
		cpy = vec_memcpy(cpy, data, 4096 * (size - 1));
	free(data);
	return (cpy);
}

t_triangle *tri_memcpy(t_triangle *dest, t_triangle *src, size_t n)
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

t_triangle *tri_add_size(t_triangle *data, int size)
{
	t_triangle	*cpy;

	if (!(cpy = malloc(sizeof(t_triangle) * (4096 * size))))
		exit (0);
	if (size > 1)
		cpy = tri_memcpy(cpy, data, 4096 * (size - 1));
	free(data);
	return (cpy);
}

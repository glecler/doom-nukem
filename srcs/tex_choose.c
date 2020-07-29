/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_choose.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

int	ft_assign_tex_tri(int *tex, t_link_list *link)
{
	tex[0] = link->link.floor_tex;
	tex[1] = link->link.top_tex;
	tex[2] = link->link.wall_tex;
	return (0);
}

int	ft_tex_choose_tri_top(t_e_data *e_data)
{
	int i;
	int tex;

	i = 1;
	tex = (e_data->tex[0])[1];
	while (i < 2)
	{
		if (tex != (e_data->tex[i])[1])
			return (NONE);
		i++;
	}
	if (i == 2)
		return ((e_data->tex[i])[1]);
	return (NONE);
}

int	ft_tex_choose_tri_floor(t_e_data *e_data)
{
	int i;
	int tex;

	i = 1;
	tex = (e_data->tex[0])[0];
	while (i < 2)
	{
		if (tex != (e_data->tex[i])[0])
			return (NONE);
		i++;
	}
	if (i == 2)
		return ((e_data->tex[i])[0]);
	return (NONE);
}

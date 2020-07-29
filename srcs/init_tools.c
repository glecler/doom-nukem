/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

void	ft_set_rgb(unsigned char *rgb, int r, int g, int b)
{
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}

t_node	ft_set_node(t_node node, int x, int y, int z)
{
	node.x = x;
	node.y = y;
	node.z = z;
	return (node);
}

int		ft_init_textures(t_win_data *w_data)
{
	int w;
	int h;

	w = 0;
	h = 0;
	(w_data->ux_textures[0]).img_ptr = mlx_xpm_file_to_image(w_data->mlx_ptr,
		"./map_editor//assets/toolbar.xpm", &w, &h);
	(w_data->ux_textures[1]).img_ptr = mlx_xpm_file_to_image(w_data->mlx_ptr,
		"./map_editor/assets/file.xpm", &w, &h);
	(w_data->ux_textures[2]).img_ptr = mlx_xpm_file_to_image(w_data->mlx_ptr,
		"./map_editor/assets/draw.xpm", &w, &h);
	(w_data->ux_textures[3]).img_ptr = mlx_xpm_file_to_image(w_data->mlx_ptr,
		"./map_editor/assets/link.xpm", &w, &h);
	(w_data->ux_textures[4]).img_ptr = mlx_xpm_file_to_image(w_data->mlx_ptr,
		"./map_editor/assets/tools.xpm", &w, &h);
	(w_data->ux_textures[5]).img_ptr = mlx_xpm_file_to_image(w_data->mlx_ptr,
		"./map_editor/assets/tex_menu.xpm", &w, &h);
	if (!((w_data->ux_textures[0]).img_ptr) ||
		!((w_data->ux_textures[1]).img_ptr) ||
			!((w_data->ux_textures[2]).img_ptr) ||
				!((w_data->ux_textures[3]).img_ptr) ||
					!((w_data->ux_textures[4]).img_ptr) ||
						!((w_data->ux_textures[5]).img_ptr))
		ft_error(FAILED_NEW_TEX);
	return (0);
}

int		ft_init_editor_data(t_e_data *e_data, t_win_data *w_data,
	t_list *list, t_llist *llist)
{
	e_data->win_data = w_data;
	e_data->llist = llist;
	e_data->list = list;
	e_data->mode = NONE;
	e_data->select_state = SELECT_NONE;
	e_data->draw_state = DRAW_NONE;
	e_data->link_state = FIRST_NODE;
	e_data->display_mode = ALL;
	e_data->buff.a = ft_set_node(e_data->buff.a, 1, 1, 0);
	e_data->buff.b = ft_set_node(e_data->buff.b, 1, 1, 0);
	ft_set_rgb(e_data->win_data->rgb, 0, 0, 127);
	ft_set_rgb(e_data->win_data->green, 120, 240, 120);
	e_data->win_data->buff_img_ptr = mlx_new_image(w_data->mlx_ptr, 1000, 800);
	e_data->win_data->buff_addr = mlx_get_data_addr(e_data->win_data->
		buff_img_ptr, &w_data->bpp, &w_data->size_line, &w_data->endian);
	if (!e_data->win_data->buff_img_ptr || !e_data->win_data->img_ptr)
		ft_error(FAILED_NEW_IMAGE);
	if (!(e_data->buff_link = (t_link*)malloc(sizeof(t_link))))
		ft_error(FAILED_MALLOC);
	ft_init_textures(w_data);
	return (0);
}

int		ft_init_win_data(t_win_data *win_data)
{
	win_data->mlx_ptr = 0;
	win_data->win_ptr = 0;
	win_data->img_ptr = 0;
	win_data->bpp = 0;
	win_data->endian = 0;
	win_data->size_line = 0;
	win_data->addr = 0;
	return (1);
}

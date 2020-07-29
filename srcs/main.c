/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

int	ft_map_edit(t_win_data *w_data, t_list *list)
{
	t_e_data	editor_data;
	t_llist		*llist;

	if (!(llist = (t_llist*)malloc(sizeof(t_llist))))
		ft_error(FAILED_LIST_ALLOC);
	llist->first = NULL;
	ft_init_editor_data(&editor_data, w_data, list, llist);
	ft_draw_axis(w_data->addr, w_data->green, w_data->size_line);
	mlx_put_image_to_window(w_data->mlx_ptr, w_data->win_ptr,
		w_data->img_ptr, 0, 0);
	mlx_put_image_to_window(w_data->mlx_ptr, w_data->win_ptr,
		w_data->ux_textures[0].img_ptr, 0, 0);
	mlx_mouse_hook(w_data->win_ptr, &ft_get_mouse, &editor_data);
	mlx_hook(w_data->win_ptr, 6, (1L << 6), &ft_get_motion, &editor_data);
	mlx_key_hook(w_data->win_ptr, &ft_get_key, &editor_data);
	mlx_loop(w_data->mlx_ptr);
	return (0);
}

int	ft_mlx_win_gen(t_list *list)
{
	t_win_data	win_data;

	ft_init_win_data(&win_data);
	if (!(win_data.mlx_ptr = mlx_init()))
		ft_error(FAILED_INIT_MLX);
	if (!(win_data.win_ptr = mlx_new_window(win_data.mlx_ptr,
		1000, 800, "MaP EditoR")))
		ft_error(FAILED_NEW_WIN);
	win_data.img_ptr = mlx_new_image(win_data.mlx_ptr, 1000, 800);
	win_data.addr = mlx_get_data_addr(win_data.img_ptr,
		&win_data.bpp, &win_data.size_line, &win_data.endian);
	if (!(win_data.img_ptr) || !(win_data.addr))
		ft_error(FAILED_NEW_IMAGE);
	ft_map_edit(&win_data, list);
	return (1);
}

int	main(void)
{
	t_list	*list;

	if (!(list = (t_list*)malloc(sizeof(t_list))))
		ft_error(FAILED_LIST_ALLOC);
	list->first = NULL;
	list->list_size = 0;
	ft_mlx_win_gen(list);
	return (0);
}

#include "../includes/doom_editor.h"

int ft_display_map(t_e_data *e_data)
{
	ft_draw_axis(e_data->win_data->addr,
		e_data->win_data->green, e_data->win_data->size_line);
	mlx_put_image_to_window(e_data->win_data->mlx_ptr,
		e_data->win_data->win_ptr, e_data->win_data->img_ptr, 0, 0);
	mlx_put_image_to_window(e_data->win_data->mlx_ptr,
		e_data->win_data->win_ptr, e_data->win_data->ux_textures[0].img_ptr, 0, 0);
	if (e_data->mode == TEX_CHOOSE)
		mlx_put_image_to_window(e_data->win_data->mlx_ptr,
			e_data->win_data->win_ptr, e_data->win_data->ux_textures[5].img_ptr, 330, 200);
	return (0);
}

int ft_set_rgb_type(unsigned char *rgb, int type, int dmode)
{
	if (type == TOP_FLOOR_WALL && dmode == ALL)
		ft_set_rgb(rgb, 0, 215, 255);
	else if ((type == FLOOR && (dmode == ALL || dmode == FLOOR)) || (type == TOP_FLOOR_WALL && dmode == FLOOR) || (type == TOP_FLOOR && dmode == FLOOR) || (type == FLOOR_WALL && dmode == FLOOR))
		ft_set_rgb(rgb, 120, 240, 120);
	else if ((type == WALL && (dmode == ALL || dmode == WALL)) || (type == TOP_FLOOR_WALL && dmode == WALL) || (type == FLOOR_WALL && dmode == WALL) || (type == TOP_WALL && dmode == WALL))
		ft_set_rgb(rgb, 0, 0, 240);
	else if (type == FLOOR_WALL && dmode == ALL)
		ft_set_rgb(rgb, 226, 43, 138);
	else if (type == TOP_WALL && dmode == ALL)
		ft_set_rgb(rgb, 0, 165, 255);
	else if ((type == TOP && (dmode == ALL || dmode == TOP)) || (type == TOP_FLOOR_WALL && dmode == TOP) || (type == TOP_FLOOR && dmode == TOP) || (type == TOP_WALL && dmode == TOP))
		ft_set_rgb(rgb, 240, 0, 0);
	else if (type == TOP_FLOOR && dmode == ALL)
		ft_set_rgb(rgb, 254, 105, 180);
	return (0);
}

int ft_update_map(t_e_data *e_data)
{
	t_node_list *buff;
	t_link_list *link_buff;

	ft_flush_img(&e_data->win_data->addr);
	ft_clean_links(e_data->llist);
	buff = e_data->list->first;
	link_buff = e_data->llist->first;
	while (buff)
	{
		ft_big_pixel_img(e_data->win_data->addr, buff->node,
			e_data->win_data->green, e_data);
		buff = buff->next;
	}
	while (link_buff)
	{
		ft_set_rgb(e_data->win_data->rgb, 0, 0, 0);
		ft_set_rgb_type(e_data->win_data->rgb, link_buff->type, e_data->display_mode);
		if (link_buff->link.node_a && link_buff->link.node_b)
			ft_put_line_img(link_buff->link.node_a->node,
				link_buff->link.node_b->node, e_data->win_data->addr, e_data);
		link_buff = link_buff->next;
	}
	ft_display_map(e_data);
	return (0);
}

int ft_draw_axis(char *addr, unsigned char *rgb, int size_line)
{   
	int x;
	int y;

	x = 0;
	while (x < 1000)
	{
		y = 50;
		while (y < 800)
		{
			ft_put_pixel_img(addr, x, y * size_line, rgb);
			y += 20;
		}
		x += 20;
	}
	return (0);
}
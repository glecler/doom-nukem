#include "../includes/doom_editor.h"

int ft_motion_draw_mode(int x, int y, t_e_data *e_data, int type)
{
	int i;

	i = -1;
	if (e_data->draw_state == DRAW_NONE)
		return (0);
	if (e_data->draw_state == DRAW_NODE)
	{
		if (type == WALL)
			ft_set_rgb(e_data->win_data->rgb, 0, 0, 240);
		if (type == FLOOR)
			ft_set_rgb(e_data->win_data->rgb, 120, 240, 120);
		e_data->buff.b = ft_set_node(e_data->buff.b, x, y, 0);
		while (++i < 3200000)
			e_data->win_data->buff_addr[i] = e_data->win_data->addr[i];
		ft_draw_axis((e_data->win_data->buff_addr), e_data->win_data->green, e_data->win_data->size_line);
		ft_put_line_img(e_data->buff.a, e_data->buff.b, e_data->win_data->buff_addr, e_data);
		mlx_put_image_to_window(e_data->win_data->mlx_ptr, e_data->win_data->win_ptr,
			e_data->win_data->buff_img_ptr, 0, 0);
		mlx_put_image_to_window(e_data->win_data->mlx_ptr, e_data->win_data->win_ptr,
			(e_data->win_data->ux_textures[0]).img_ptr, 0, 0);
	}
	return (0);
}

int ft_motion_select_mode(int x, int y, t_e_data *e_data)
{
	if (e_data->select_state == SELECT_NONE)
		return (0);
	if (e_data->select_state == SELECT_NODE)
	{
		e_data->selected_node->node.x = x;
		e_data->selected_node->node.y = y;
		ft_update_map(e_data);
	}
	return (0);
}

int ft_motion_z_mode(int y, t_e_data *e_data)
{
	if (e_data->select_state == SELECT_NONE)
		return (0);
	if (e_data->select_state == SELECT_NODE)
	{
		e_data->selected_node->node.z = e_data->selected_node->node.y - y;
		ft_update_map(e_data);
	}
	return (0);
}
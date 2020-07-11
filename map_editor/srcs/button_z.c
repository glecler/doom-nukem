#include "../includes/doom_editor.h"

int ft_button_mod_z_none(int x, int y, int button, t_e_data *e_data)
{
	if (!(e_data->selected_node = ft_selected_node(x, y, e_data)) || button != 1)
		return (0);
	ft_big_pixel_img(e_data->win_data->addr, e_data->selected_node->node, e_data->win_data->rgb, e_data);
	e_data->select_state = SELECT_NODE;
	return (0);
}

int ft_button_z_mode(int x, int y, int button, t_e_data *e_data)
{
	if (button != 1)
		return (0);
	if (e_data->select_state == SELECT_NONE)
		ft_button_mod_z_none(x, y, button, e_data);
	else if (e_data->select_state == SELECT_NODE)
		e_data->select_state = SELECT_NONE;
	return (0);
}
#include "../includes/doom_editor.h"

int	ft_type(int type, int added_type)
{
	if ((type == WALL && added_type == FLOOR) ||
		(type == FLOOR && added_type == WALL))
		type = FLOOR_WALL;
	else if ((type == WALL && added_type == TOP) ||
		(type == TOP && added_type == WALL))
		type = TOP_WALL;
	else if ((type == FLOOR_WALL && added_type == TOP))
		type = TOP_FLOOR_WALL;
	else if ((type == FLOOR && added_type == TOP) ||
		(type == TOP && added_type == FLOOR))
		type = TOP_FLOOR;
	else if (type == TOP_FLOOR && added_type == WALL)
		type = TOP_FLOOR_WALL;
	else if (type == TOP_WALL && added_type == FLOOR)
		type = TOP_FLOOR_WALL;
	return (type);
}

int	ft_button_link_second_node(t_e_data *e_data, t_node_list *buff, int type)
{
	e_data->buff_link->node_b = buff;
	e_data->buff_link->node_b->node.type = ft_type(buff->node.type, type);
	buff->node.type = ft_type(buff->node.type, type);
	ft_add_to_llist(*(e_data->buff_link), e_data->llist, type);
	if (ft_intersect_all_llist(e_data->llist) == 0)
		ft_big_pixel_img(e_data->win_data->addr,
			buff->node, e_data->win_data->rgb, e_data);
	else
		ft_delete_last_link(e_data->llist);
	e_data->link_state = FIRST_NODE;
	ft_update_map(e_data);
	return (0);
}

int	ft_button_link_mode_wall(int button, int x, int y, t_e_data *e_data)
{
	t_node_list	*buff;

	if (!(buff = ft_selected_node(x, y, e_data)) || button != 1)
		return (0);
	if (e_data->link_state == FIRST_NODE)
	{
		e_data->buff_link->node_a = buff;
		e_data->buff_link->node_a->node.type = ft_type(buff->node.type, WALL);
		buff->node.type = ft_type(buff->node.type, WALL);
		ft_big_pixel_img(e_data->win_data->addr, buff->node,
			e_data->win_data->rgb, e_data);
		ft_display_map(e_data);
		e_data->link_state = SECOND_NODE;
	}
	else
		ft_button_link_second_node(e_data, buff, WALL);
	return (0);
}

int	ft_button_link_mode_floor(int button, int x, int y, t_e_data *e_data)
{
	t_node_list *buff;

	if (!(buff = ft_selected_node(x, y, e_data)) || button != 1)
		return (0);
	if (e_data->link_state == FIRST_NODE)
	{
		e_data->buff_link->node_a = buff;
		e_data->buff_link->node_a->node.type = ft_type(buff->node.type, FLOOR);
		buff->node.type = ft_type(buff->node.type, FLOOR);
		ft_big_pixel_img(e_data->win_data->addr, buff->node,
			e_data->win_data->green, e_data);
		ft_display_map(e_data);
		e_data->link_state = SECOND_NODE;
	}
	else
		ft_button_link_second_node(e_data, buff, FLOOR);
	return (0);
}

int	ft_button_link_mode_top(int button, int x, int y, t_e_data *e_data)
{
	t_node_list *buff;

	if (!(buff = ft_selected_node(x, y, e_data)) || button != 1)
		return (0);
	if (buff->type == FLOOR)
		return (0);
	if (e_data->link_state == FIRST_NODE)
	{
		e_data->buff_link->node_a = buff;
		e_data->buff_link->node_a->node.type = ft_type(buff->node.type, TOP);
		buff->node.type = ft_type(buff->node.type, TOP);
		ft_big_pixel_img(e_data->win_data->addr, buff->node,
			e_data->win_data->green, e_data);
		ft_display_map(e_data);
		e_data->link_state = SECOND_NODE;
	}
	else
		ft_button_link_second_node(e_data, buff, TOP);
	return (0);
}

#include "../includes/doom_editor.h"

int	ft_but_d_mode_lft_clkn(int x, int y, t_e_data *e_data, int type)
{
	e_data->buff.a = ft_set_node(e_data->buff.a, x, y, 10);
	e_data->draw_state = DRAW_NODE;
	ft_big_pixel_img(e_data->win_data->addr, e_data->buff.a,
		e_data->win_data->green, e_data);
	ft_add_to_list(ft_create_node(x, y, 10, type), e_data->list);
	ft_update_map(e_data);
	return (0);
}

int	ft_but_d_mode_lft_clk(int x, int y, t_e_data *e_data, int type)
{
	if (e_data->draw_state == DRAW_NONE && x > 0 && y > 42)
		ft_but_d_mode_lft_clkn(x, y, e_data, type);
	else if (e_data->draw_state == DRAW_NODE && x > 0 && y > 42)
	{
		e_data->buff.b = ft_set_node(e_data->buff.b, x, y, 10);
		e_data->buff.type = type;
		if (ft_intersect_llist(e_data->buff, e_data->llist) == 0)
		{
			ft_big_pixel_img(e_data->win_data->addr, e_data->buff.b,
				e_data->win_data->green, e_data);
			e_data->buff.a = ft_set_node(e_data->buff.a, x, y, 10);
			ft_add_to_list(ft_create_node(x, y, 10, type), e_data->list);
			ft_add_to_llist(ft_set_link((ft_last_node(e_data->list))->prev,
				ft_last_node(e_data->list)), e_data->llist, type);
		}
	}
	return (0);
}

int	ft_but_d_mode_rgt_clk(int x, int y, t_e_data *e_data, int type)
{
	t_node_list *buff;

	buff = ft_selected_node(x, y, e_data);
	e_data->buff.b = ft_set_node(e_data->buff.b, x, y, 10);
	e_data->buff.type = type;
	if (ft_intersect_llist(e_data->buff, e_data->llist) == 0)
	{
		if (buff)
		{
			e_data->buff_link->node_a = ft_last_node(e_data->list);
			e_data->buff_link->node_b = buff;
			ft_add_to_llist(*(e_data->buff_link), e_data->llist, type);
			e_data->draw_state = DRAW_NONE;
			return (0);
		}
		ft_add_to_list(ft_create_node(x, y, 10, type), e_data->list);
		ft_add_to_llist(ft_set_link((ft_last_node(e_data->list))->prev,
			ft_last_node(e_data->list)), e_data->llist, type);
		ft_big_pixel_img(e_data->win_data->addr, e_data->buff.b,
			e_data->win_data->green, e_data);
		e_data->draw_state = DRAW_NONE;
	}
	return (0);
}

int	ft_button_draw_mode_wall(int button, int x, int y, t_e_data *e_data)
{
	if (button == 1)
		ft_button_draw_mode_left_click(x, y, e_data, WALL);
	if (button == 2 && e_data->draw_state == DRAW_NODE && x > 0 && y > 42)
		ft_button_draw_mode_right_click(x, y, e_data, WALL);
	ft_update_map(e_data);
	return (0);
}

int	ft_button_draw_mode_floor(int button, int x, int y, t_e_data *e_data)
{
	if (button == 1)
		ft_button_draw_mode_left_click(x, y, e_data, FLOOR);
	if (button == 2 && e_data->draw_state == DRAW_NODE && x > 0 && y > 42)
		ft_button_draw_mode_right_click(x, y, e_data, FLOOR);
	ft_update_map(e_data);
	return (0);
}

int	ft_button_draw_top(int button, int x, int y, t_e_data *e_data)
{
	if (button == 1)
		ft_button_draw_mode_left_click(x, y, e_data, TOP);
	if (button == 2 && e_data->draw_state == DRAW_NODE && x > 0 && y > 42)
		ft_button_draw_mode_right_click(x, y, e_data, TOP);
	ft_update_map(e_data);
	return (0);
}
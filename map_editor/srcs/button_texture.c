#include "../includes/doom_editor.h"

int ft_choose_texture(int button, int x, int y, t_e_data *e_data)
{
	mlx_put_image_to_window(e_data->win_data->mlx_ptr,
		e_data->win_data->win_ptr, e_data->win_data->ux_textures[5].img_ptr, 330, 200);
	if (x < 574 && x > 514 && y > 320 && y < 380)
		e_data->curr_tex = PROTO_ORA;
	else if (x < 440 && x > 378 && y > 320 && y < 380)
		e_data->curr_tex = PROTO_VIO;
	else if (x < 440 && x > 378 && y > 460 && y < 525)
		e_data->curr_tex = PROTO_VIOT;
	else if (x < 578 && x > 515 && y > 462 && y < 525)
		e_data->curr_tex = PROTO_VERT;
	else
		return (0);
	e_data->mode = TOOL_TEXTURES;
	ft_update_map(e_data);
	return (0);
}

t_link_list *ft_selected_link(t_e_data *e_data)
{
	t_link_list *link;

	link = e_data->llist->first;
	while (link)
	{
		if ((link->link.node_a == e_data->buff_link->node_a && link->link.node_b == e_data->buff_link->node_b) || (link->link.node_a == e_data->buff_link->node_b && link->link.node_b == e_data->buff_link->node_a))
			return (link);
		link = link->next;
	}
	return (NULL);
}

int ft_assign_tex(t_link_list *link, t_e_data *e_data)
{
	if (e_data->display_mode == ALL || e_data->display_mode == FLOOR)
	{
		link->link.floor_tex = e_data->curr_tex;
		link->link.node_a->floor_tex = e_data->curr_tex;
		link->link.node_b->floor_tex = e_data->curr_tex;
	}
	if (e_data->display_mode == ALL || e_data->display_mode == TOP)
	 {
		link->link.top_tex = e_data->curr_tex;
		link->link.node_a->top_tex = e_data->curr_tex;
		link->link.node_b->top_tex = e_data->curr_tex;
	}   
	if (e_data->display_mode == ALL || e_data->display_mode == WALL)
	{
		link->link.wall_tex = e_data->curr_tex;
		link->link.node_a->wall_tex = e_data->curr_tex;
		link->link.node_b->wall_tex = e_data->curr_tex;
	}
	return (0);
}

int ft_button_textures(int button, int x, int y, t_e_data *e_data)
{
	t_node_list *buff;
	t_link_list *buff_link;

	if (!(buff = ft_selected_node(x, y, e_data)) || button == 0)
		return (0);
	if (e_data->link_state == FIRST_NODE)
	{
		e_data->buff_link->node_a = buff;
		ft_big_pixel_img(e_data->win_data->addr, buff->node, e_data->win_data->blue, e_data);
		ft_display_map(e_data);
		e_data->link_state = SECOND_NODE;
	}
	else
	{
		e_data->buff_link->node_b = buff;
		if ((buff_link = ft_selected_link(e_data)))
			ft_assign_tex(buff_link, e_data);
		e_data->link_state = FIRST_NODE;
		ft_update_map(e_data);
	}
	return (0);
}
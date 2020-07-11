#include "../includes/doom_editor.h"

int ft_tex_choose_tri_top(t_e_data *e_data)
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
int ft_tex_choose_tri_floor(t_e_data *e_data)
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
int ft_add_triangle_top(t_node_list *node, t_link_list *buff, int no[4], t_e_data *e_data)
{
	if ((node == buff->link.node_a ? buff->link.node_b :
		buff->link.node_a)->no == no[0])
	{
		if ((buff->type == TOP || buff->type == TOP_WALL || buff->type ==
			TOP_FLOOR_WALL || buff->type == TOP_FLOOR))
			ft_add_to_tlist(ft_create_triangle(no[0] + 1, no[1] + 1, no[2]
				+ 1), e_data->tlist, ft_tex_choose_tri_top(e_data));
	}
	return (0);
}

int ft_assign_tex_tri(int *tex, t_link_list *link)
{
	tex[0] = link->link.floor_tex;
	tex[1] = link->link.top_tex;
	tex[2] = link->link.wall_tex; 
	return (0);      
}

int ft_triangle_from_node_top(t_node_list *node, int vertex, t_e_data *e_data, int no[4])
{
	t_link_list *buff;

	buff = e_data->llist->first;
	while (buff)
	{
		if ((buff->link.node_a == node || buff->link.node_b == node) &&
			(buff->active == 0) && (buff->type == TOP || buff->type == TOP_WALL
				|| buff->type == TOP_FLOOR_WALL || buff->type == TOP_FLOOR))
		{
			no[vertex] = node->no;
			ft_assign_tex_tri(e_data->tex[vertex], buff);
			buff->active = 1;
			if (vertex < 2)
				ft_triangle_from_node_top(node == buff->link.node_a ? buff->link.node_b
					: buff->link.node_a, vertex + 1, e_data, no);
			else if (vertex == 2)
				ft_add_triangle_top(node, buff, no, e_data);
			buff->active = 0;
		}
		buff = buff->next;
	}
	return (0);
}

int ft_add_triangle_floor(t_node_list *node, t_link_list *buff, int no[4], t_e_data *e_data)
{
	if ((node == buff->link.node_a ? buff->link.node_b :
		buff->link.node_a)->no == no[0])
	{
		if ((buff->type == FLOOR || buff->type == FLOOR_WALL ||
			buff->type == TOP_FLOOR_WALL || buff->type == TOP_FLOOR))
			ft_add_to_tlist(ft_create_triangle(no[0], no[1], no[2]),
				e_data->tlist, ft_tex_choose_tri_floor(e_data));
	}
	return (0);
}

int ft_triangle_from_node_floor(t_node_list *node, int vertex, t_e_data *e_data, int no[4])
{
	t_link_list *buff;

	buff = e_data->llist->first;
	while (buff)
	{
		if ((buff->link.node_a == node || buff->link.node_b == node) &&
			(buff->active == 0) && (buff->type == FLOOR || buff->type == FLOOR_WALL
				|| buff->type == TOP_FLOOR_WALL || buff->type == TOP_FLOOR))
		{
			no[vertex] = node->no;
			ft_assign_tex_tri(e_data->tex[vertex], buff);
			buff->active = 1;
			if (vertex < 2)
				ft_triangle_from_node_floor(node == buff->link.node_a ?
					buff->link.node_b : buff->link.node_a, vertex + 1, e_data, no);
			else if (vertex == 2)
				ft_add_triangle_floor(node, buff, no, e_data);
			buff->active = 0;
		}
		buff = buff->next;
	}
	return (0);
}
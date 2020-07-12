#include "../includes/doom_editor.h"

int	ft_node_from_node(t_node_list *node, t_node_list *goal, t_e_data *e_data)
{
	t_link_list *buff;

	buff = e_data->llist->first;
	while (buff)
	{
		if ((buff->link.node_a == node || buff->link.node_b == node)
			&& (buff->active == 0))
		{
			buff->active = 1;
			if (buff->link.node_a == goal || buff->link.node_b == goal)
				return (1);
			return (ft_node_from_node(node == buff->link.node_a ?
				buff->link.node_b : buff->link.node_a, goal, e_data));
			buff->active = 0;
		}
		buff = buff->next;
	}
	return (0);
}

int	ft_add_floor_link(t_node_list *node, t_e_data *e_data)
{
	t_node_list	*buff;
	t_segment	segment;

	buff = e_data->list->first;
	while (buff)
	{
		ft_init_llist_active(e_data->llist);
		if (buff != node && (buff->node.type == FLOOR ||
			buff->node.type == FLOOR_WALL || buff->node.type ==
				TOP_FLOOR_WALL || buff->node.type == TOP_FLOOR)
					&& ft_node_from_node(node, buff, e_data) == 1)
		{
			segment.a = ft_create_node(node->node.x, node->node.y,
				node->node.z, node->type);
			segment.b = ft_create_node(buff->node.x, buff->node.y,
				buff->node.z, buff->type);
			segment.type = FLOOR;
			if (ft_intersect_llist(segment, e_data->llist) == 0)
				ft_add_to_llist(ft_set_link(node, buff), e_data->llist, FLOOR);
		}
		buff = buff->next;
	}
	return (0);
}

int	ft_add_top_link(t_node_list *node, t_e_data *e_data)
{
	t_node_list	*buff;
	t_segment	segment;

	buff = e_data->list->first;
	while (buff)
	{
		ft_init_llist_active(e_data->llist);
		if (buff != node && (buff->node.type == TOP || buff->node.type
			== TOP_FLOOR_WALL || buff->node.type == TOP_WALL ||
			buff->node.type == TOP_FLOOR) &&
				ft_node_from_node(node, buff, e_data) == 1)
		{
			segment.a = ft_create_node(node->node.x, node->node.y,
				node->node.z, node->type);
			segment.b = ft_create_node(buff->node.x, buff->node.y,
				buff->node.z, buff->type);
			segment.type = TOP;
			if (ft_intersect_llist(segment, e_data->llist) == 0)
				ft_add_to_llist(ft_set_link(node, buff), e_data->llist, TOP);
		}
		buff = buff->next;
	}
	return (0);
}

int	ft_triangulate_polygon_top(t_e_data *e_data)
{
	t_node_list	*node;

	node = e_data->list->first;
	while (node)
	{
		if (node->node.type == TOP_FLOOR_WALL || node->node.type == TOP_WALL
			|| node->node.type == TOP || node->node.type == TOP_FLOOR)
			ft_add_top_link(node, e_data);
		node = node->next;
	}
	ft_init_llist_active(e_data->llist);
	return (1);
}

int	ft_triangulate_polygon_floor(t_e_data *e_data)
{
	t_node_list *node;
	t_node_list *buff;

	node = e_data->list->first;
	while (node)
	{
		buff = e_data->list->first;
		if (node->node.type == FLOOR || node->node.type == FLOOR_WALL
			|| node->node.type == TOP_FLOOR_WALL || node->node.type ==
				TOP_FLOOR)
			ft_add_floor_link(node, e_data);
		node = node->next;
	}
	ft_init_llist_active(e_data->llist);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

int	ft_add_triangle_top(t_node_list *node, t_link_list *buff,
	int no[4], t_e_data *e_data)
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

int	ft_triangle_from_node_top(t_node_list *node,
	int vertex, t_e_data *e_data, int no[4])
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
				ft_triangle_from_node_top(node == buff->link.node_a ?
					buff->link.node_b : buff->link.node_a, vertex + 1
						, e_data, no);
			else if (vertex == 2)
				ft_add_triangle_top(node, buff, no, e_data);
			buff->active = 0;
		}
		buff = buff->next;
	}
	return (0);
}

int	ft_add_triangle_floor(t_node_list *node, t_link_list *buff,
	int no[4], t_e_data *e_data)
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

int	ft_triangle_from_node_floor(t_node_list *node, int vertex,
	t_e_data *e_data, int no[4])
{
	t_link_list *buff;

	buff = e_data->llist->first;
	while (buff)
	{
		if ((buff->link.node_a == node || buff->link.node_b == node) &&
			(buff->active == 0) && (buff->type == FLOOR ||
				buff->type == FLOOR_WALL
				|| buff->type == TOP_FLOOR_WALL || buff->type == TOP_FLOOR))
		{
			no[vertex] = node->no;
			ft_assign_tex_tri(e_data->tex[vertex], buff);
			buff->active = 1;
			if (vertex < 2)
				ft_triangle_from_node_floor(node == buff->link.node_a ?
					buff->link.node_b : buff->link.node_a, vertex + 1
						, e_data, no);
			else if (vertex == 2)
				ft_add_triangle_floor(node, buff, no, e_data);
			buff->active = 0;
		}
		buff = buff->next;
	}
	return (0);
}

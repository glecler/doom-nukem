/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

int	ft_on_segment(t_node x, t_node y, t_node z)
{
	if (y.x <= fmax(x.x, z.x) && y.x >= fmin(x.x, z.x) &&
	y.y <= fmax(x.y, z.y) && y.y >= fmin(x.y, z.y))
		return (1);
	return (0);
}

int	ft_find_orientation(t_node x, t_node y, t_node z)
{
	int ret;

	ret = (y.y - x.y) * (z.x - y.x) - (y.x - x.x) * (z.y - y.y);
	if (ret == 0)
		return (0);
	return (ret > 0 ? 1 : 2);
}

int	ft_intersect(t_segment buff, t_segment list)
{
	int o1;
	int o2;
	int o3;
	int o4;

	o1 = ft_find_orientation(buff.a, buff.b, list.a);
	o2 = ft_find_orientation(buff.a, buff.b, list.b);
	o3 = ft_find_orientation(list.a, list.b, buff.a);
	o4 = ft_find_orientation(list.a, list.b, buff.b);
	if (o1 != o2 && o3 != o4)
		return (1);
	if (o1 == 0 && ft_on_segment(buff.a, list.a, buff.b) == 1)
		return (1);
	if (o2 == 0 && ft_on_segment(buff.a, list.b, buff.b) == 1)
		return (1);
	if (o3 == 0 && ft_on_segment(list.a, buff.a, list.b) == 1)
		return (1);
	if (o4 == 0 && ft_on_segment(list.a, buff.b, list.b) == 1)
		return (1);
	return (0);
}

int	ft_int_type(int type1, int type2)
{
	if ((type1 == TOP && type2 == FLOOR) || (type1 == FLOOR && type2 == TOP))
		return (1);
	if ((type1 == FLOOR_WALL && type2 == TOP) || (type2 == FLOOR_WALL
		&& type1 == TOP))
		return (1);
	if ((type1 == TOP && type2 == WALL) || (type2 == TOP && type1 == WALL))
		return (1);
	if ((type1 == TOP_WALL && type2 == FLOOR) || (type1 == TOP_WALL &&
		type2 == FLOOR))
		return (1);
	if ((type1 == TOP_FLOOR && type2 == WALL) || (type1 == TOP_FLOOR &&
		type2 == WALL))
		return (1);
	if ((type1 == WALL && type2 == FLOOR) || (type1 == FLOOR && type2 == WALL))
		return (1);
	return (0);
}

int	ft_intersect_llist(t_segment buff, t_llist *llist)
{
	t_link_list	*link;
	t_segment	llist_buff;

	link = llist->first;
	while (link)
	{
		llist_buff.a.x = link->link.node_a->node.x;
		llist_buff.a.y = link->link.node_a->node.y;
		llist_buff.b.x = link->link.node_b->node.x;
		llist_buff.b.y = link->link.node_b->node.y;
		if (ft_intersect(buff, llist_buff) == 1 && (buff.a.x != llist_buff.b.x
			|| buff.a.y != llist_buff.b.y) && (buff.b.x != llist_buff.a.x
				|| buff.b.y != llist_buff.a.y) && (buff.a.x != llist_buff.a.x
					|| buff.a.y != llist_buff.a.y) && (buff.b.x !=
						llist_buff.b.x || buff.b.y != llist_buff.b.y)
							&& (ft_int_type(link->type, buff.type) == 0))
			return (1);
		link = link->next;
	}
	return (0);
}

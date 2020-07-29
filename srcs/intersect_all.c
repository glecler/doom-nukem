/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2020/07/29 16:30:13 by gregoirel        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

t_segment	ft_assign_segment(t_node a, t_node b)
{
	t_segment x;

	x.a.x = a.x;
	x.a.y = a.y;
	x.b.x = b.x;
	x.b.y = b.y;
	return (x);
}

int			ft_intersect_all_part(t_llist *llist, t_segment x,
	t_link_list *link)
{
	t_link_list *buff_link;
	t_segment	y;

	buff_link = llist->first;
	while (buff_link)
	{
		if (buff_link->link.node_a && buff_link->link.node_b
			&& buff_link != link)
		{
			y = ft_assign_segment(buff_link->link.node_a->node,
				buff_link->link.node_b->node);
			if (ft_intersect(x, y) == 1 && (x.a.x != y.b.x ||
				x.a.y != y.b.y) && (x.b.x != y.a.x || x.b.y != y.a.y)
					&& (x.a.x != y.a.x || x.a.y != y.a.y) && (x.b.x != y.b.x
						|| x.b.y != y.b.y) && (ft_int_type(link->type,
							buff_link->type) == 0))
				return (1);
		}
		buff_link = buff_link->next;
	}
	return (0);
}

int			ft_intersect_all_llist(t_llist *llist)
{
	t_link_list	*link;
	t_segment	x;

	link = llist->first;
	while (link)
	{
		if (link->link.node_a && link->link.node_b)
		{
			x = ft_assign_segment(link->link.node_a->node,
				link->link.node_b->node);
			if (ft_intersect_all_part(llist, x, link) == 1)
				return (1);
		}
		link = link->next;
	}
	return (0);
}

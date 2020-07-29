/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

int			ft_init_llist_active(t_llist *llist)
{
	t_link_list	*link;

	link = llist->first;
	while (link)
	{
		link->active = 0;
		link = link->next;
	}
	return (0);
}

int			ft_assign_number(t_list *list)
{
	t_node_list	*node;
	int			i;

	i = 1;
	node = list->first;
	while (node)
	{
		node->no = i;
		i += 2;
		node = node->next;
	}
	return (0);
}

int			ft_clean_triangles(t_tlist *tlist)
{
	t_triangle_list *buff;
	t_triangle_list *tri;

	tri = tlist->first;
	while (tri)
	{
		buff = tlist->first;
		while (buff)
		{
			if (buff != tri)
			{
				if (ft_is_tri_equal(buff->triangle, tri->triangle) == 1)
					ft_delete_triangle(buff, tlist);
			}
			buff = buff->next;
		}
		tri = tri->next;
	}
	return (0);
}

int			ft_is_tri_equal(t_triangle tri1, t_triangle tri2)
{
	if (tri1.a == tri2.a && tri1.b == tri2.b && tri1.c == tri2.c)
		return (1);
	if (tri1.a == tri2.b && tri1.b == tri2.a && tri1.c == tri2.c)
		return (1);
	if (tri1.a == tri2.a && tri1.b == tri2.c && tri1.c == tri2.b)
		return (1);
	if (tri1.a == tri2.c && tri1.b == tri2.a && tri1.c == tri2.b)
		return (1);
	if (tri1.a == tri2.c && tri1.b == tri2.b && tri1.c == tri2.a)
		return (1);
	if (tri1.a == tri2.b && tri1.b == tri2.c && tri1.c == tri2.a)
		return (1);
	return (0);
}

t_triangle	ft_create_triangle(int a, int b, int c)
{
	t_triangle triangle;

	triangle.a = a;
	triangle.b = b;
	triangle.c = c;
	return (triangle);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

void	ft_error(int errno)
{
	if (errno == FAILED_NEW_IMAGE)
		ft_putstr("error : image creation failed\n");
	if (errno == FAILED_LIST_ALLOC)
		ft_putstr("error : list allocation failed\n");
	if (errno == FAILED_INIT_MLX)
		ft_putstr("error : MLX initialisation failed\n");
	if (errno == FAILED_NEW_WIN)
		ft_putstr("error : window creation failed\n");
	if (errno == FAILED_NEW_TEX)
		ft_putstr("error : texture image creation failed\n");
	if (errno == FAILED_MALLOC)
		ft_putstr("error : memory allocation failed\n");
	if (errno == FAILED_READ_FILE)
		ft_putstr("error : reading file failed\n");
	if (errno == FAILED_OPEN_FILE)
		ft_putstr("error : opening file failed\n");
	if (errno == FAILED_WRITE_FILE)
		ft_putstr("error : writing to file failed\n");
	if (errno == FAILED_WRITE_DATA)
		ft_putstr("error : saving data failed\n");
	if (errno == FAILED_NODE_ALLOC)
		ft_putstr("error : node allocation failed\n");
	exit(0);
}

t_node	ft_create_node(double x, double y, double z, int type)
{
	t_node node;

	node.x = x;
	node.y = y;
	node.z = z;
	node.type = type;
	return (node);
}

void	ft_coord_swap(t_node *a, t_node *b)
{
	a->x += b->x;
	b->x = a->x - b->x;
	a->x -= b->x;
	a->y += b->y;
	b->y = a->y - b->y;
	a->y -= b->y;
	a->z += b->z;
	b->z = a->z - b->z;
	a->z -= b->z;
}

t_link	ft_set_link(t_node_list *a, t_node_list *b)
{
	t_link link;

	link.node_a = a;
	link.node_b = b;
	if (link.node_a->floor_tex == link.node_b->floor_tex)
		link.floor_tex = link.node_a->floor_tex;
	if (link.node_a->top_tex == link.node_b->top_tex)
		link.top_tex = link.node_a->top_tex;
	if (link.node_a->wall_tex == link.node_b->wall_tex)
		link.wall_tex = link.node_a->wall_tex;
	return (link);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_strjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

char	*ft_wall_strjoin1(t_link_list *link_buff, char *data)
{
	data = ft_strjoin_free_s1(data, "f ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(link_buff->link.node_a->no));
	data = ft_strjoin_free_s1(data, "/2 ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(link_buff->link.node_b->no + 1));
	data = ft_strjoin_free_s1(data, "/3 ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(link_buff->link.node_b->no));
	data = ft_strjoin_free_s1(data, "/4\nf ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(link_buff->link.node_a->no));
	data = ft_strjoin_free_s1(data, "/2 ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(link_buff->link.node_a->no + 1));
	data = ft_strjoin_free_s1(data, "/1 ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(link_buff->link.node_b->no + 1));
	data = ft_strjoin_free_s1(data, "/3\n");
	return (data);
}

char	*ft_wall_strjoin2(t_link_list *link_buff, char *data)
{
	data = ft_strjoin_free_s1(data, "f ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(link_buff->link.node_b->no));
	data = ft_strjoin_free_s1(data, "/4 ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(link_buff->link.node_b->no + 1));
	data = ft_strjoin_free_s1(data, "/3 ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(link_buff->link.node_a->no));
	data = ft_strjoin_free_s1(data, "/2\nf ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(link_buff->link.node_b->no + 1));
	data = ft_strjoin_free_s1(data, "/3 ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(link_buff->link.node_a->no + 1));
	data = ft_strjoin_free_s1(data, "/1 ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(link_buff->link.node_a->no));
	data = ft_strjoin_free_s1(data, "/2\n");
	return (data);
}

char	*ft_tri_strjoin(t_triangle_list *t_buff, char *data)
{
	data = ft_strjoin_free_s1(data, "f ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(t_buff->triangle.a));
	data = ft_strjoin_free_s1(data, "/1 ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(t_buff->triangle.b));
	data = ft_strjoin_free_s1(data, "/2 ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(t_buff->triangle.c));
	data = ft_strjoin_free_s1(data, "/3\n");
	data = ft_strjoin_free_s1(data, "f ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(t_buff->triangle.c));
	data = ft_strjoin_free_s1(data, "/3 ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(t_buff->triangle.b));
	data = ft_strjoin_free_s1(data, "/2 ");
	data = ft_strjoin_free_s1s2(data, ft_itoa(t_buff->triangle.a));
	data = ft_strjoin_free_s1(data, "/1\n");
	return (data);
}

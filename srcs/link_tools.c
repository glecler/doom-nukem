/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

t_node_list	*ft_last_node(t_list *list)
{
	t_node_list *buff;

	buff = list->first;
	if (buff->next)
	{
		while (buff->next)
			buff = buff->next;
	}
	return (buff);
}

t_node_list	*ft_selected_node(int x, int y, t_e_data *e_data)
{
	t_node_list *buff;

	buff = e_data->list->first;
	while (buff)
	{
		if (buff->node.x < x + 10 && buff->node.x > x - 10 &&
			buff->node.y < y + 10 && buff->node.y > y - 10)
			return (buff);
		else
			buff = buff->next;
	}
	return (NULL);
}

int			ft_delete_links_node(t_node_list *buff, t_llist *llist)
{
	t_link_list *link_buff;

	link_buff = llist->first;
	while (link_buff)
	{
		if (link_buff->link.node_a == buff)
			ft_delete_link(link_buff, llist);
		else if (link_buff->link.node_b == buff)
			ft_delete_link(link_buff, llist);
		link_buff = link_buff->next;
	}
	return (0);
}

int			ft_delete_last_link(t_llist *llist)
{
	t_link_list *buff;

	buff = llist->first;
	while (buff->next)
		buff = buff->next;
	ft_delete_link(buff, llist);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

void	ft_delete_node(t_node_list *node, t_list *list)
{
	if (node->next == NULL && node->prev == NULL)
	{
		list->first = NULL;
		free(node);
	}
	else if (node->next == NULL && node->prev != NULL)
	{
		node->prev->next = NULL;
		free(node);
	}
	else if (node->prev == NULL && node->next != NULL)
	{
		list->first = node->next;
		node->next->prev = NULL;
		free(node);
	}
	else
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
		free(node);
	}
	list->list_size -= 1;
}

int		ft_set_node_list(t_node node, t_node_list *buff)
{
	buff->node = node;
	buff->next = NULL;
	buff->prev = NULL;
	buff->floor_tex = NONE;
	buff->top_tex = NONE;
	buff->wall_tex = NONE;
	return (0);
}

int		ft_add_to_list(t_node node, t_list *list)
{
	t_node_list *buff;

	buff = list->first;
	if (buff == NULL)
	{
		if (!(buff = (t_node_list*)malloc(sizeof(t_node_list))))
			ft_error(FAILED_NODE_ALLOC);
		ft_set_node_list(node, buff);
		list->first = buff;
		return (0);
	}
	else
	{
		while (buff->next != NULL)
			buff = buff->next;
		if (!(buff->next = (t_node_list*)malloc(sizeof(t_node_list))))
			ft_error(FAILED_NODE_ALLOC);
		ft_set_node_list(node, buff->next);
		buff->next->prev = buff;
		buff->next->prev->next = buff->next;
	}
	list->list_size += 1;
	return (0);
}

int		ft_free_list(t_list *list)
{
	t_node_list *buff;
	t_node_list *del_buff;

	buff = list->first;
	while (buff)
	{
		del_buff = buff;
		ft_delete_node(del_buff, list);
		buff = buff->next;
	}
	free(list);
	return (0);
}

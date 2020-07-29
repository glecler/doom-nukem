/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

void	ft_delete_link(t_link_list *link, t_llist *llist)
{
	if (link->next == NULL && link->prev == NULL)
	{
		llist->first = NULL;
		free(link);
	}
	else if (link->next == NULL && link->prev != NULL)
	{
		link->prev->next = NULL;
		free(link);
	}
	else if (link->prev == NULL && link->next != NULL)
	{
		llist->first = link->next;
		link->next->prev = NULL;
		free(link);
	}
	else
	{
		link->next->prev = link->prev;
		link->prev->next = link->next;
		free(link);
	}
}

int		ft_set_link_list(t_link_list *buff, t_link link, int type)
{
	buff->link = link;
	buff->active = 0;
	buff->type = type;
	buff->next = NULL;
	buff->prev = NULL;
	return (0);
}

int		ft_add_to_llist(t_link link, t_llist *llist, int type)
{
	t_link_list *buff;

	buff = llist->first;
	if (buff == NULL)
	{
		if (!(buff = (t_link_list*)malloc(sizeof(t_link_list))))
			ft_error(FAILED_NODE_ALLOC);
		ft_set_link_list(buff, link, type);
		llist->first = buff;
		return (0);
	}
	while (buff->next != NULL)
		buff = buff->next;
	if (!(buff->next = (t_link_list*)malloc(sizeof(t_link_list))))
		ft_error(FAILED_LINK_ALLOC);
	ft_set_link_list(buff->next, link, type);
	buff->next->prev = buff;
	buff->next->prev->next = buff->next;
	return (0);
}

int		ft_free_llist(t_llist *llist)
{
	t_link_list *buff;
	t_link_list *del_buff;

	buff = llist->first;
	while (buff)
	{
		del_buff = buff;
		ft_delete_link(del_buff, llist);
		buff = buff->next;
	}
	free(llist);
	return (0);
}

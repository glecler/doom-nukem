#include "../includes/doom_editor.h"

int	ft_delete_link_type(t_link_list *link, t_link_list *buff, t_llist *llist)
{
	if (!ft_delete_1_links(link, buff, llist))
	{
		if (!ft_delete_2_links(link, buff, llist))
			ft_delete_3_links(link, buff, llist);
	}
	return (0);
}

int	ft_delete_2_links(t_link_list *link, t_link_list *buff, t_llist *llist)
{
	if (buff->type == link->type)
	{
		ft_delete_link(buff, llist);
		return (1);
	}
	if ((buff->type == FLOOR && link->type == WALL) ||
		(buff->type == WALL && link->type == FLOOR))
	{
		ft_delete_link(buff, llist);
		link->type = FLOOR_WALL;
		return (1);
	}
	if ((buff->type == WALL && link->type == TOP) ||
		(buff->type == TOP && link->type == WALL))
	{
		link->type = TOP_WALL;
		ft_delete_link(buff, llist);
		return (1);
	}
	return (0);
}

int	ft_delete_3_links(t_link_list *link, t_link_list *buff, t_llist *llist)
{
	if ((buff->type == FLOOR && link->type == TOP) ||
		(buff->type == TOP && link->type == FLOOR))
	{
		link->type = TOP_FLOOR;
		ft_delete_link(buff, llist);
	}
	else if ((buff->type == FLOOR_WALL && link->type == FLOOR) ||
		(buff->type == FLOOR && link->type == FLOOR_WALL))
	{
		link->type = FLOOR_WALL;
		ft_delete_link(buff, llist);
	}
	return (0);
}

int	ft_delete_1_links(t_link_list *link, t_link_list *buff, t_llist *llist)
{
	if ((buff->type == FLOOR && link->type == TOP_WALL) ||
		(buff->type == TOP_WALL && link->type == FLOOR))
	{
		link->type = TOP_FLOOR_WALL;
		ft_delete_link(buff, llist);
		return (1);
	}
	if ((buff->type == FLOOR_WALL && link->type == TOP) ||
		(buff->type == TOP && link->type == FLOOR_WALL))
	{
		link->type = TOP_FLOOR_WALL;
		ft_delete_link(buff, llist);
		return (1);
	}
	if (link->type == TOP_FLOOR_WALL)
	{
		ft_delete_link(buff, llist);
		return (1);
	}
	return (0);
}

int	ft_clean_links(t_llist *llist)
{
	t_link_list *buff;
	t_link_list *link;

	link = llist->first;
	while (link)
	{
		buff = llist->first;
		while (buff)
		{
			if (buff != link && ((buff->link.node_a == link->link.node_b
				&& buff->link.node_b == link->link.node_a) ||
					(buff->link.node_a ==
					link->link.node_a && buff->link.node_b ==
						link->link.node_b)))
				ft_delete_link_type(link, buff, llist);
			buff = buff->next;
		}
		link = link->next;
	}
	return (0);
}

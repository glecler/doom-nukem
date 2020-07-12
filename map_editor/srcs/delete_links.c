#include "../includes/doom_editor.h"

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

int	ft_delete_4_links(t_link_list *link, t_link_list *buff, t_llist *llist)
{
	if ((link->type == TOP_WALL && buff->type == WALL) ||
		(link->type == WALL && buff->type == TOP_WALL))
	{
		link->type = TOP_WALL;
		ft_delete_link(buff, llist);
		return (1);
	}
	if ((link->type == TOP_FLOOR && buff->type == TOP) ||
		(link->type == TOP && buff->type == TOP_FLOOR))
	{
		link->type = TOP_FLOOR;
		ft_delete_link(buff, llist);
		return (1);
	}
	if ((link->type == TOP_FLOOR && buff->type == FLOOR) ||
		(link->type == FLOOR && buff->type == TOP_FLOOR))
	{
		link->type = TOP_FLOOR;
		ft_delete_link(buff, llist);
		return (1);
	}
	return (0);
}

int	ft_delete_5_links(t_link_list *link, t_link_list *buff, t_llist *llist)
{
	if (link->type == TOP_FLOOR_WALL)
	{
		ft_delete_link(buff, llist);
		return (1);
	}
	if ((link->type == FLOOR_WALL && buff->type == WALL) ||
		(link->type == WALL && buff->type == FLOOR_WALL))
	{
		link->type = FLOOR_WALL;
		ft_delete_link(buff, llist);
		return (1);
	}
	if ((link->type == TOP_WALL && buff->type == TOP) ||
		(link->type == TOP && buff->type == TOP_WALL))
	{
		link->type = TOP_WALL;
		ft_delete_link(buff, llist);
		return (1);
	}
	return (0);
}

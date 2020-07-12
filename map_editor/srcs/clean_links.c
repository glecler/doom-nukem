#include "../includes/doom_editor.h"

int	ft_delete_link_type(t_link_list *link, t_link_list *buff, t_llist *llist)
{
	if (ft_delete_1_links(link, buff, llist) == 1)
		return (1);
	if (ft_delete_2_links(link, buff, llist) == 1)
		return (1);
	if (ft_delete_3_links(link, buff, llist) == 1)
		return (1);
	if (ft_delete_4_links(link, buff, llist) == 1)
		return (1);
	if (ft_delete_5_links(link, buff, llist) == 1)
		return (1);
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
				&& buff->link.node_b == link->link.node_a)
					|| (buff->link.node_a == link->link.node_a
						&& buff->link.node_b == link->link.node_b)))
				ft_delete_link_type(link, buff, llist);
			buff = buff->next;
		}
		link = link->next;
	}
	return (0);
}

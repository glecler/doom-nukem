#include "../includes/doom_editor.h"

int		ft_link_to_triangle(t_tlist *tlist, t_e_data *e_data)
{
	t_node_list	*node;
	int			i;
	int			no[4];

	i = 0;
	while (i < 3)
		no[i++] = 0;
	e_data->tlist = tlist;
	node = e_data->list->first;
	while (node)
	{
		ft_triangle_from_node_floor(node, 0, e_data, no);
		ft_init_llist_active(e_data->llist);
		ft_triangle_from_node_top(node, 0, e_data, no);
		node = node->next;
	}
	ft_clean_triangles(e_data->tlist);
	return (1);
}

int		ft_fill_tlist(t_tlist *tlist, t_e_data *e_data)
{
	if (!(ft_triangulate_polygon_floor(e_data)))
		return (0);
	if (!(ft_triangulate_polygon_top(e_data)))
		return (0);
	if (!(ft_link_to_triangle(tlist, e_data)))
		return (0);
	return (1);
}

t_tlist	*ft_create_triangles(t_e_data *e_data)
{
	t_tlist *tlist;

	tlist = NULL;
	if (!(tlist = (t_tlist*)malloc(sizeof(t_tlist))))
		ft_error(FAILED_LIST_ALLOC);
	tlist->first = NULL;
	if (!(ft_fill_tlist(tlist, e_data)))
		ft_error(FAILED_TLIST_FILL);
	return (tlist);
}

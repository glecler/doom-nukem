#include "../includes/doom_editor.h"

void	ft_delete_triangle(t_triangle_list *triangle, t_tlist *tlist)
{
	if (triangle->next == NULL && triangle->prev == NULL)
	{
		tlist->first = NULL;
		free(triangle);
	}
	else if (triangle->next == NULL && triangle->prev != NULL)
	{
		triangle->prev->next = NULL;
		free(triangle);
	}
	else if (triangle->prev == NULL && triangle->next != NULL)
	{
		tlist->first = triangle->next;
		triangle->next->prev = NULL;
		free(triangle);
	}
	else
	{
		triangle->next->prev = triangle->prev;
		triangle->prev->next = triangle->next;
		free(triangle);
	}
}

int		ft_set_triangle_list(t_triangle triangle, int tex,
	t_triangle_list *buff)
{
	buff->triangle = triangle;
	buff->triangle.tex = tex;
	buff->next = NULL;
	buff->prev = NULL;
	return (0);
}

int		ft_add_to_tlist(t_triangle triangle, t_tlist *tlist, int tex)
{
	t_triangle_list *buff;

	buff = tlist->first;
	if (buff == NULL)
	{
		if (!(buff = (t_triangle_list*)malloc(sizeof(t_triangle_list))))
			ft_error(FAILED_MALLOC);
		ft_set_triangle_list(triangle, tex, buff);
		tlist->first = buff;
		return (0);
	}
	else
	{
		while (buff->next != NULL)
			buff = buff->next;
		if (!(buff->next = (t_triangle_list*)malloc(sizeof(t_triangle_list))))
			ft_error(FAILED_MALLOC);
		ft_set_triangle_list(triangle, tex, buff->next);
		buff->next->prev = buff;
		buff->next->prev->next = buff->next;
	}
	return (0);
}

int		ft_free_tlist(t_tlist *tlist)
{
	t_triangle_list *buff;
	t_triangle_list *del_buff;

	buff = tlist->first;
	while (buff)
	{
		del_buff = buff;
		ft_delete_triangle(del_buff, tlist);
		buff = buff->next;
	}
	free(tlist);
	return (0);
}
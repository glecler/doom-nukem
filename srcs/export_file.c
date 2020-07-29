/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

char	*ft_export_v(t_e_data *e_data, char *data)
{
	t_node_list	*buff;

	buff = e_data->list->first;
	while (buff)
	{
		data = ft_strjoin(data, "v ");
		data = ft_strjoin(data, ft_itoa(buff->node.x / 5));
		data = ft_strjoin(data, " ");
		data = ft_strjoin(data, ft_itoa(buff->node.z / 5));
		data = ft_strjoin(data, " ");
		data = ft_strjoin(data, ft_itoa(buff->node.y / 5));
		data = ft_strjoin(data, "\n");
		data = ft_strjoin(data, "v ");
		data = ft_strjoin(data, ft_itoa(buff->node.x / 5));
		data = ft_strjoin(data, " ");
		data = ft_strjoin(data, ft_itoa(buff->node.z / 5 + 20));
		data = ft_strjoin(data, " ");
		data = ft_strjoin(data, ft_itoa(buff->node.y / 5));
		data = ft_strjoin(data, "\n");
		buff = buff->next;
	}
	return (data);
}

char	*ft_xpm_tex(int tex_code)
{
	char	*ret;

	if (tex_code == PROTO_ORA)
	{
		if (!(ret = ft_strdup("proto_ora.xpm\n")))
			ft_error(FAILED_MALLOC);
	}
	else if (tex_code == PROTO_VIO)
	{
		if (!(ret = ft_strdup("proto_vio.xpm\n")))
			ft_error(FAILED_MALLOC);
	}
	else if (tex_code == PROTO_VIOT)
	{
		if (!(ret = ft_strdup("proto_vio_trans.xpm\n")))
			ft_error(FAILED_MALLOC);
	}
	else if (tex_code == PROTO_VERT)
	{
		if (!(ret = ft_strdup("proto_vert.xpm\n")))
			ft_error(FAILED_MALLOC);
	}
	else if (!(ret = ft_strdup("grey.xpm\n")))
		ft_error(FAILED_MALLOC);
	return (ret);
}

char	*ft_export_walls(t_e_data *e_data, char *data)
{
	t_link_list *link_buff;

	link_buff = e_data->llist->first;
	while (link_buff)
	{
		if (link_buff->type == WALL || link_buff->type == FLOOR_WALL
			|| link_buff->type == TOP_FLOOR_WALL || link_buff->type == TOP_WALL)
		{
			data = ft_strjoin(data, "o newobject\n");
			data = ft_strjoin(data, "usemtl ");
			data = ft_strjoin(data, ft_xpm_tex(link_buff->link.wall_tex));
			data = ft_strjoin(data, "s 1\n");
			data = ft_strjoin(data, "id 8\n");
			data = ft_wall_strjoin1(link_buff, data);
			data = ft_wall_strjoin2(link_buff, data);
		}
		link_buff = link_buff->next;
	}
	return (data);
}

char	*ft_export_floor_top(t_e_data *e_data, char *data)
{
	t_tlist			*tlist;
	t_triangle_list	*t_buff;

	tlist = ft_create_triangles(e_data);
	t_buff = tlist->first;
	while (t_buff)
	{
		data = ft_strjoin(data, "o newobject\n");
		data = ft_strjoin(data, "usemtl ");
		data = ft_strjoin(data, ft_xpm_tex(t_buff->triangle.tex));
		data = ft_strjoin(data, "s 1\n");
		data = ft_strjoin(data, "id 7\n");
		data = ft_tri_strjoin(t_buff, data);
		t_buff = t_buff->next;
	}
	ft_free_tlist(tlist);
	return (data);
}

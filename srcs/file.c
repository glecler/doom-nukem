/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

int		ft_new_file(t_e_data *e_data)
{
	if (e_data->list)
		ft_free_list(e_data->list);
	if (e_data->llist)
		ft_free_llist(e_data->llist);
	ft_flush_img(&e_data->win_data->addr);
	ft_flush_img(&e_data->win_data->buff_addr);
	ft_display_map(e_data);
	if (!(e_data->list = (t_list*)malloc(sizeof(t_list))))
		ft_error(FAILED_LIST_ALLOC);
	if (!(e_data->llist = (t_llist*)malloc(sizeof(t_llist))))
		ft_error(FAILED_LIST_ALLOC);
	e_data->llist->first = NULL;
	e_data->list->first = NULL;
	e_data->list->list_size = 0;
	e_data->draw_state = DRAW_NONE;
	e_data->mode = DRAW_WALL;
	return (0);
}

int		ft_export_file(t_e_data *e_data)
{
	int		fd;
	char	*filename;
	int		i;

	if (!(filename = ft_strdup("new_map.obj")))
		ft_error(FAILED_MALLOC);
	i = 0;
	while ((fd = open(filename, O_RDONLY)) > 0)
	{
		i++;
		free(filename);
		close(fd);
		filename = ft_strdup("new_map ");
		filename = ft_strjoin_free_s1(filename, "(");
		filename = ft_strjoin_free_s1s2(filename, ft_itoa(i));
		filename = ft_strjoin_free_s1(filename, ").obj");
	}
	if (!(fd = open(filename, O_CREAT | O_WRONLY)))
		ft_error(FAILED_OPEN_FILE);
	free(filename);
	if (ft_export_data_to_save(e_data, fd) == -1)
		ft_error(FAILED_WRITE_DATA);
	ft_update_map(e_data);
	close(fd);
	return (0);
}

char	*ft_join_mtl(char *data)
{
	data = ft_strjoin_free_s1(data, "\n\nusemtl grey.xpm\nusemtl fin.xpm\n");
	data = ft_strjoin_free_s1(data, "usemtl orbe.xpm\nusemtl orbe_grise.xpm\n");
	data = ft_strjoin_free_s1(data, "usemtl tableau.xpm\nusemtl tableau.xpm\n");
	data = ft_strjoin_free_s1(data,
		"usemtl portal.xpm\nusemtl proto_vert.xpm\n");
	data = ft_strjoin_free_s1(data, "usemtl g_talk.xpm\nusemtl weapon.xpm\n");
	data = ft_strjoin_free_s1(data, "usemtl laser.xpm\nusemtl jauge_5.xpm\n");
	data = ft_strjoin_free_s1(data, "usemtl jauge_4.xpm\nusemtl jauge_3.xpm\n");
	data = ft_strjoin_free_s1(data, "usemtl jauge_2.xpm\nusemtl jauge_1.xpm\n");
	data = ft_strjoin_free_s1(data, "usemtl jauge_0.xpm\nusemtl jauge.xpm\n");
	data = ft_strjoin_free_s1(data, "usemtl none.xpm\n");
	return (data);
}

int		ft_export_data_to_save(t_e_data *e_data, int fd)
{
	char	*data;

	ft_assign_number(e_data->list);
	data = ft_strnew(0);
	data = ft_strjoin_free_s1(data, "spawn 20 100 20\n");
	data = ft_export_v(e_data, data);
	data = ft_strjoin_free_s1(data, "vt 0 0\nvt 0 1\nvt 1 0\nvt 1 1\n");
	data = ft_export_walls(e_data, data);
	data = ft_export_floor_top(e_data, data);
	data = ft_join_mtl(data);
	if (!data)
		ft_error(FAILED_WRITE_DATA);
	if (write(fd, data, ft_strlen(data)) == -1)
		return (-1);
	free(data);
	return (0);
}

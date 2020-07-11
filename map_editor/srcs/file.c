#include "../includes/doom_editor.h"

int ft_new_file(t_editor_data *e_data)
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

int ft_export_file(t_editor_data *e_data)
{
    int fd;
    char *filename;
    int i;

    if (!(filename = ft_strdup("new_map.obj")))
        ft_error(FAILED_MALLOC);
    i = 0;
    while ((fd = open(filename, O_RDONLY)) > 0)
    {
        i++;
        free(filename);
        close(fd);
        filename = ft_strdup("new_map ");
        filename = ft_strjoin(filename, "(");
        filename = ft_strjoin(filename, ft_itoa(i));
        filename = ft_strjoin(filename, ").obj");
    }
    if (!(fd = open(filename, O_CREAT | O_WRONLY)))
            ft_error(FAILED_OPEN_FILE);
    if (ft_export_data_to_save(e_data, fd) == -1)
            ft_error(FAILED_WRITE_DATA);
    close(fd);
    return (0);
}

int ft_export_data_to_save(t_editor_data *e_data, int fd)
{
    char *data;

    ft_assign_number(e_data->list);
    data = ft_strnew(0);
    data = ft_strjoin(data, "spawn 20 100 20\n");
    data = ft_export_v(e_data, data);
    data = ft_strjoin(data, "vt 0 0\nvt 0 1\nvt 1 0\nvt 1 1\n");
    data = ft_export_walls(e_data, data);
    data = ft_export_floor_top(e_data, data);
    data = ft_strjoin(data, "\n\nusemtl grey.xpm\nusemtl fin.xpm\nusemtl orbe.xpm\nusemtl orbe_grise.xpm\nusemtl tableau.xpm\nusemtl tableau.xpm\nusemtl portal.xpm\nusemtl proto_vert.xpm\nusemtl g_talk.xpm\nusemtl weapon.xpm\nusemtl laser.xpm\nusemtl jauge_5.xpm\nusemtl jauge_4.xpm\nusemtl jauge_3.xpm\nusemtl jauge_2.xpm\nusemtl jauge_1.xpm\nusemtl jauge_0.xpm\nusemtl jauge.xpm\nusemtl none.xpm");
    if (!data)
        ft_error(FAILED_WRITE_DATA);
    if (write(fd, data, ft_strlen(data)) == -1)
        return (-1);
    free(data);
    return (0);
}

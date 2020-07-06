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
    remove("new_map.obj");
    return (0);
}

int ft_export_file(t_editor_data *e_data)
{
    int fd;

    remove("new_map.obj");
    if (!(fd = open("new_map.obj", O_CREAT | O_WRONLY)))
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
    data = ft_strjoin(data, "mtllib vase.mtl\n");
    data = ft_export_v(e_data, data);
    data = ft_strjoin(data, "vt 0 0\nvt 0 1\nvt 1 0\nvt 1 1\n");
    data = ft_export_walls(e_data, data);
    data = ft_export_floor_top(e_data, data);
    if (!data)
        ft_error(FAILED_WRITE_DATA);
    if (write(fd, data, ft_strlen(data)) == -1)
        return (-1);
    free(data);
    return (0);
}

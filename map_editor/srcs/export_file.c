#include "../includes/doom_editor.h"

char *ft_export_v(t_editor_data *e_data, char *data)
{    
    t_node_list *buff;
    
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

char *ft_xpm_tex(int tex_code)
{
    char *ret;

    if (tex_code == PROTO_ORA)
    {
        if (!(ret = ft_strdup("proto_ora.xpm\n")))
            ft_error(FAILED_MALLOC);
        return (ret);
    }
    if (tex_code == PROTO_VIO)
    {
        if (!(ret = ft_strdup("proto_vio.xpm\n")))
            ft_error(FAILED_MALLOC);
        return (ret);
    }
    if (tex_code == PROTO_VIOT)
    {
        if (!(ret = ft_strdup("proto_vio_trans.xpm\n")))
            ft_error(FAILED_MALLOC);
        return (ret);
    }
    if (tex_code == PROTO_VERT)
    {
        if (!(ret = ft_strdup("proto_vert.xpm\n")))
            ft_error(FAILED_MALLOC);
        return (ret);
    }
    if (!(ret = ft_strdup("grey.xpm\n")))
        ft_error(FAILED_MALLOC);
    return (ret);
}

char *ft_export_walls(t_editor_data *e_data, char *data)
{
    t_link_list *link_buff;

    link_buff = e_data->llist->first;
    while (link_buff)
    {
        if (link_buff->type == WALL || link_buff->type == FLOOR_WALL || link_buff->type == TOP_FLOOR_WALL || link_buff->type == TOP_WALL)
        {
            data = ft_strjoin(data, "o newobject\n");
            data = ft_strjoin(data, "usemtl ");
            data = ft_strjoin(data, ft_xpm_tex(link_buff->link.wall_tex));
            data = ft_strjoin(data, "id 8\n");
            data = ft_strjoin(data, "f ");
            data = ft_strjoin(data, ft_itoa(link_buff->link.node_a->no));
            data = ft_strjoin(data, "/2 ");
            data = ft_strjoin(data, ft_itoa(link_buff->link.node_b->no + 1));
            data = ft_strjoin(data, "/3 ");
            data = ft_strjoin(data, ft_itoa(link_buff->link.node_b->no));
            data = ft_strjoin(data, "/4\nf ");
            data = ft_strjoin(data, ft_itoa(link_buff->link.node_a->no));
            data = ft_strjoin(data, "/2 ");
            data = ft_strjoin(data, ft_itoa(link_buff->link.node_a->no + 1));
            data = ft_strjoin(data, "/1 ");
            data = ft_strjoin(data, ft_itoa(link_buff->link.node_b->no + 1));
            data = ft_strjoin(data, "/3\n");
            data = ft_strjoin(data, "f ");            
            data = ft_strjoin(data, ft_itoa(link_buff->link.node_b->no));
            data = ft_strjoin(data, "/4 ");
            data = ft_strjoin(data, ft_itoa(link_buff->link.node_b->no + 1));
            data = ft_strjoin(data, "/3 ");
            data = ft_strjoin(data, ft_itoa(link_buff->link.node_a->no));
            data = ft_strjoin(data, "/2\nf ");
            data = ft_strjoin(data, ft_itoa(link_buff->link.node_b->no + 1));
            data = ft_strjoin(data, "/3 ");
            data = ft_strjoin(data, ft_itoa(link_buff->link.node_a->no + 1));
            data = ft_strjoin(data, "/1 ");
            data = ft_strjoin(data, ft_itoa(link_buff->link.node_a->no));
            data = ft_strjoin(data, "/2\n");
        }
        link_buff = link_buff->next;
    }
    return (data);
}

char *ft_export_floor_top(t_editor_data *e_data, char *data)
{
    t_tlist *tlist;
    t_triangle_list *t_buff;
    
    tlist = ft_create_triangles(e_data);
    t_buff = tlist->first;
    while (t_buff)
    {
            data = ft_strjoin(data, "o newobject\n");
            data = ft_strjoin(data, "usemtl ");
            data = ft_strjoin(data, ft_xpm_tex(t_buff->triangle.tex));
            data = ft_strjoin(data, "id 7\n");
            data = ft_strjoin(data, "f ");
            data = ft_strjoin(data, ft_itoa(t_buff->triangle.a));
            data = ft_strjoin(data, "/1 ");
            data = ft_strjoin(data, ft_itoa(t_buff->triangle.b));
            data = ft_strjoin(data, "/2 ");
            data = ft_strjoin(data, ft_itoa(t_buff->triangle.c));
            data = ft_strjoin(data, "/3\n");
            data = ft_strjoin(data, "f ");
            data = ft_strjoin(data, ft_itoa(t_buff->triangle.c));
            data = ft_strjoin(data, "/3 ");
            data = ft_strjoin(data, ft_itoa(t_buff->triangle.b));
            data = ft_strjoin(data, "/2 ");
            data = ft_strjoin(data, ft_itoa(t_buff->triangle.a));
            data = ft_strjoin(data, "/1\n");
            t_buff = t_buff->next;
    }
    return (data);
}
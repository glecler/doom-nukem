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

char *ft_export_walls(t_editor_data *e_data, char *data)
{
    t_link_list *link_buff;

    link_buff = e_data->llist->first;
    while (link_buff)
    {
        if (link_buff->type == WALL || link_buff->type == FLOOR_WALL || link_buff->type == TOP_FLOOR_WALL || link_buff->type == TOP_WALL)
        {
            data = ft_strjoin(data, "o newobject\n");
            data = ft_strjoin(data, "usemtl proto_vio_trans.xpm\n");
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
            data = ft_strjoin(data, "usemtl proto_ora.xpm\n");
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
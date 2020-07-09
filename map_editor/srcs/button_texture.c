#include "../includes/doom_editor.h"

int ft_button_textures(int button, int x, int y, t_editor_data *e_data)
{
    t_node_list *buff;

    if (!(buff = ft_selected_node(x, y, e_data)) || button != 1)
        return (0);
    if (e_data->link_state == FIRST_NODE)
    {
        e_data->buff_link->link.node_a = buff;
        ft_big_pixel_img(e_data->win_data->addr, buff->node, e_data->win_data->rgb, e_data);
        ft_display_map(e_data);
        e_data->link_state = SECOND_NODE;
    }
    else
    {
        e_data->buff_link->link.node_b = buff;
        // change type 
        e_data->link_state = FIRST_NODE;
        ft_update_map(e_data);
    }
}
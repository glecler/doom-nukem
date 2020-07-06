#include "../includes/doom_editor.h"

int ft_button_select_mode_none(int x, int y, t_editor_data *e_data)
{
    if (!(e_data->selected_node = ft_selected_node(x, y, e_data)))
        return (0);
    e_data->select_state = SELECT_NODE;
    return (0);
}

int ft_button_select_mode_node(t_editor_data *e_data)
{
    if (ft_intersect_all_llist(e_data->llist) == 0)
        e_data->select_state = SELECT_NONE;
    return (0);
}

int ft_button_select_mode(int button, int x, int y, t_editor_data *e_data)
{
    if (button != 1)
        return (0);
    if (e_data->select_state == SELECT_NONE)
        ft_button_select_mode_none(x, y, e_data);
    else if (e_data->select_state == SELECT_NODE)
        ft_button_select_mode_node(e_data);
    return (0);
}
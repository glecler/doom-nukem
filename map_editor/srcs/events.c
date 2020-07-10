#include "../includes/doom_editor.h"

int ft_menu_choose_mode(int x, int y, t_editor_data *e_data)
{
    if (e_data->mode == MENU_FILE)
        ft_file_interact(x, y, e_data);
    else if (e_data->mode == MENU_DRAW)
        ft_mode_interact(x, y, e_data);
    else if (e_data->mode == MENU_TOOL)
        ft_tool_interact(x, y, e_data);
    else if (e_data->mode == MENU_LINK)
        ft_link_interact(x, y, e_data);
    return (0);
}

int ft_draw_choose_mode(int button, int x, int y, t_editor_data *e_data)
{
    if (e_data->mode == DRAW_WALL)
        ft_button_draw_mode_wall(button, x, y, e_data);
    else if (e_data->mode == DRAW_FLOOR)
        ft_button_draw_mode_floor(button, x, y, e_data);
    else if (e_data->mode == SELECT)
        ft_button_select_mode(button, x, y, e_data);
    else if (e_data->mode == ERASE)
        ft_button_erase_mode(button, x, y, e_data);
    return (0);
}

int ft_tool_choose_mode(int button, int x, int y, t_editor_data *e_data)
{
    if (e_data->mode == TOOL_LINK_WALL)
        ft_button_link_mode_wall(button, x, y, e_data);
    else if (e_data->mode == TOOL_LINK_FLOOR)
        ft_button_link_mode_floor(button, x, y, e_data);
    else if (e_data->mode == TOOL_LINK_TOP)
        ft_button_link_mode_top(button, x, y, e_data);
    else if (e_data->mode == TOOL_TEXTURES)
        ;//ft_button_textures(button, x, y, e_data);
    else if (e_data->mode == TOOL_Z)
        ft_button_z_mode(x, y, button, e_data);
    return (0);
}

int ft_get_mouse(int button, int x, int y, t_editor_data *e_data)
{
    if (y < 42)
        ft_banner_interact(x, y, e_data);
    else
    {
        ft_tool_choose_mode(button, x, y, e_data);
        ft_draw_choose_mode(button, x, y, e_data);
        ft_menu_choose_mode(x, y, e_data);
    }
    return (0);
}

int		ft_get_key(int key, t_editor_data *e_data)
{
	if (key == 53)
		exit(0);
	return(0);
}

int ft_get_motion(int x, int y, t_editor_data *e_data)
{
    if (e_data->mode == DRAW_FLOOR)
        ft_motion_draw_mode(x, y, e_data, FLOOR);
    if (e_data->mode == DRAW_WALL)
        ft_motion_draw_mode(x, y, e_data, WALL);
    if (e_data->mode == SELECT)
        ft_motion_select_mode(x, y, e_data);
    if (e_data->mode == TOOL_Z)
        ft_motion_z_mode(y, e_data);
    return (0);
}
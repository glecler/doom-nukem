#include "../includes/doom_editor.h"

int	ft_get_mouse(int button, int x, int y, t_e_data *e_data)
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

int	ft_get_key(int key, t_e_data *e_data)
{
	if (key == 53)
		exit(0);
	if (key == 12)
		e_data->display_mode = ALL;
	if (key == 13)
		e_data->display_mode = WALL;
	if (key == 14)
		e_data->display_mode = FLOOR;
	if (key == 15)
		e_data->display_mode = TOP;
	ft_update_map(e_data);
	return (0);
}

int	ft_get_motion(int x, int y, t_e_data *e_data)
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

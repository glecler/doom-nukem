#include "../includes/doom_editor.h"

int	ft_banner_choose(int tex, int x, int type, t_e_data *e_data)
{
	ft_display_map(e_data);
	mlx_put_image_to_window(e_data->win_data->mlx_ptr,
		e_data->win_data->win_ptr,
			e_data->win_data->ux_textures[tex].img_ptr, x, 0);
	e_data->mode = type;
	return (0);
}

int	ft_menu_choose_mode(int x, int y, t_e_data *e_data)
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

int	ft_draw_choose_mode(int button, int x, int y, t_e_data *e_data)
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

int	ft_tool_choose_mode(int button, int x, int y, t_e_data *e_data)
{
	if (e_data->mode == TOOL_LINK_WALL)
		ft_button_link_mode_wall(button, x, y, e_data);
	else if (e_data->mode == TOOL_LINK_FLOOR)
		ft_button_link_mode_floor(button, x, y, e_data);
	else if (e_data->mode == TOOL_LINK_TOP)
		ft_button_link_mode_top(button, x, y, e_data);
	else if (e_data->mode == TEX_CHOOSE)
		ft_choose_texture(x, y, e_data);
	else if (e_data->mode == TOOL_Z)
		ft_button_z_mode(x, y, button, e_data);
	else if (e_data->mode == TOOL_TEXTURES)
		ft_button_textures(button, x, y, e_data);
	return (0);
}
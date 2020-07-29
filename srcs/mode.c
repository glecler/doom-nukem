/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

int	ft_file_interact(int x, int y, t_e_data *e_data)
{
	if (x > 0 && x < 240 && y > 42 && y < 184)
	{
		if (y > 42 && y < 80)
			ft_new_file(e_data);
		if (y > 85 && y < 118)
			ft_export_file(e_data);
		e_data->mode = NONE;
	}
	ft_display_map(e_data);
	return (0);
}

int	ft_link_interact(int x, int y, t_e_data *e_data)
{
	if (x > 480 && x < 728 && y > 42 && y < 157)
	{
		if (y > 42 && y < 80)
			e_data->mode = TOOL_LINK_WALL;
		if (y > 85 && y < 118)
			e_data->mode = TOOL_LINK_FLOOR;
		if (y > 124 && y < 157)
			e_data->mode = TOOL_LINK_TOP;
	}
	ft_display_map(e_data);
	return (0);
}

int	ft_mode_interact(int x, int y, t_e_data *e_data)
{
	if (x > 268 && x < 480 && y > 42 && y < 118)
	{
		if (y > 42 && y < 80)
			e_data->mode = DRAW_WALL;
		if (y > 85 && y < 118)
			e_data->mode = DRAW_FLOOR;
	}
	ft_display_map(e_data);
	return (0);
}

int	ft_tool_interact(int x, int y, t_e_data *e_data)
{
	if (x > 728 && x < 1000 && y > 42 && y < 157)
	{
		if (y > 42 && y < 80)
			e_data->mode = SELECT;
		if (y > 85 && y < 118)
			e_data->mode = ERASE;
		if (y > 124 && y < 157)
			e_data->mode = TEX_CHOOSE;
	}
	ft_display_map(e_data);
	return (0);
}

int	ft_banner_interact(int x, int y, t_e_data *e_data)
{
	if (x > 0 && x < 240 && y < 42 && y > 0)
		ft_banner_choose(1, 0, MENU_FILE, e_data);
	else if (x > 240 && x < 480 && y < 42 && y > 0)
		ft_banner_choose(2, 240, MENU_DRAW, e_data);
	else if (x > 480 && x < 720 && y < 42 && y > 0)
		ft_banner_choose(3, 485, MENU_LINK, e_data);
	else if (x > 720 && x < 1000 && y < 42 && y > 0)
		ft_banner_choose(4, 728, MENU_TOOL, e_data);
	else
	{
		ft_display_map(e_data);
		e_data->mode = NONE;
	}
	return (0);
}

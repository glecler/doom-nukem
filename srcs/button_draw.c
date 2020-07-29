/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

int	ft_button_draw_mode_wall(int button, int x, int y, t_e_data *e_data)
{
	if (button == 1)
		ft_but_d_mode_lft_clk(x, y, e_data, WALL);
	if (button == 2 && e_data->draw_state == DRAW_NODE && x > 0 && y > 42)
		ft_but_d_mode_rgt_clk(x, y, e_data, WALL);
	ft_update_map(e_data);
	return (0);
}

int	ft_button_draw_mode_floor(int button, int x, int y, t_e_data *e_data)
{
	if (button == 1)
		ft_but_d_mode_lft_clk(x, y, e_data, FLOOR);
	if (button == 2 && e_data->draw_state == DRAW_NODE && x > 0 && y > 42)
		ft_but_d_mode_rgt_clk(x, y, e_data, FLOOR);
	ft_update_map(e_data);
	return (0);
}

int	ft_button_draw_top(int button, int x, int y, t_e_data *e_data)
{
	if (button == 1)
		ft_but_d_mode_lft_clk(x, y, e_data, TOP);
	if (button == 2 && e_data->draw_state == DRAW_NODE && x > 0 && y > 42)
		ft_but_d_mode_rgt_clk(x, y, e_data, TOP);
	ft_update_map(e_data);
	return (0);
}

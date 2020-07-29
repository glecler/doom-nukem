/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mode_clic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

int	ft_but_d_mode_lft_clkn(int x, int y, t_e_data *e_data, int type)
{
	e_data->buff.a = ft_set_node(e_data->buff.a, x, y, 0);
	e_data->draw_state = DRAW_NODE;
	ft_big_pixel_img(e_data->win_data->addr, e_data->buff.a,
		e_data->win_data->green, e_data);
	ft_add_to_list(ft_create_node(x, y, 10, type), e_data->list);
	ft_update_map(e_data);
	return (0);
}

int	ft_but_d_mode_lft_clk(int x, int y, t_e_data *e_data, int type)
{
	if (e_data->draw_state == DRAW_NONE && x > 0 && y > 42)
		ft_but_d_mode_lft_clkn(x, y, e_data, type);
	else if (e_data->draw_state == DRAW_NODE && x > 0 && y > 42)
	{
		e_data->buff.b = ft_set_node(e_data->buff.b, x, y, 0);
		e_data->buff.type = type;
		if (ft_intersect_llist(e_data->buff, e_data->llist) == 0)
		{
			ft_big_pixel_img(e_data->win_data->addr, e_data->buff.b,
				e_data->win_data->green, e_data);
			e_data->buff.a = ft_set_node(e_data->buff.a, x, y, 0);
			ft_add_to_list(ft_create_node(x, y, 10, type), e_data->list);
			ft_add_to_llist(ft_set_link((ft_last_node(e_data->list))->prev,
				ft_last_node(e_data->list)), e_data->llist, type);
		}
	}
	return (0);
}

int	ft_but_d_mode_rgt_clk(int x, int y, t_e_data *e_data, int type)
{
	t_node_list *buff;

	buff = ft_selected_node(x, y, e_data);
	e_data->buff.b = ft_set_node(e_data->buff.b, x, y, 0);
	e_data->buff.type = type;
	if (ft_intersect_llist(e_data->buff, e_data->llist) == 0)
	{
		if (buff)
		{
			e_data->buff_link->node_a = ft_last_node(e_data->list);
			e_data->buff_link->node_b = buff;
			ft_add_to_llist(*(e_data->buff_link), e_data->llist, type);
			e_data->draw_state = DRAW_NONE;
			return (0);
		}
		ft_add_to_list(ft_create_node(x, y, 0, type), e_data->list);
		ft_add_to_llist(ft_set_link((ft_last_node(e_data->list))->prev,
			ft_last_node(e_data->list)), e_data->llist, type);
		ft_big_pixel_img(e_data->win_data->addr, e_data->buff.b,
			e_data->win_data->green, e_data);
		e_data->draw_state = DRAW_NONE;
	}
	return (0);
}

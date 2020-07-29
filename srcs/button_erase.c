/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_erase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glecler <glecler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by glecler           #+#    #+#             */
/*   Updated: 2019/12/02 14:50:19 by glecler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_editor.h"

int	ft_button_erase_mode(int button, int x, int y, t_e_data *e_data)
{
	t_node_list *buff;

	buff = e_data->list->first;
	if (!(buff = ft_selected_node(x, y, e_data)) || button != 1)
		return (0);
	ft_delete_links_node(buff, e_data->llist);
	ft_delete_node(buff, e_data->list);
	ft_update_map(e_data);
	return (0);
}

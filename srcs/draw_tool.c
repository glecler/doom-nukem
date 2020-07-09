/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/10 16:55:46 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void init_bres(t_vec3d v0, t_vec3d v1, t_bres *bres)
{
	bres->x0 = v0.x;
	bres->y0 = v0.y;
	bres->x1 = v1.x;
	bres->y1 = v1.y;
	bres->dx = abs(bres->x1-bres->x0);
	bres->sx = bres->x0<bres->x1 ? 1 : -1;
	bres->dy = abs(bres->y1-bres->y0);
	bres->sy = bres->y0<bres->y1 ? 1 : -1;
	bres->err = (bres->dx>bres->dy ? bres->dx : -bres->dy)/2;
}

void drawline(t_vec3d v0, t_vec3d v1, t_sdl *sdl)
{
	t_bres bres;

	init_bres(v0, v1, &bres);
  	while(1)
	{
		SDL_RenderDrawPoint(sdl->render, bres.x0, bres.y0);
    	if (bres.x0==bres.x1 && bres.y0==bres.y1)
			break;
    	bres.e2 = bres.err;
    	if (bres.e2 >-bres.dx)
		{
			bres.err -= bres.dy;
			bres.x0 += bres.sx;
		}
    	if (bres.e2 < bres.dy)
		{
			bres.err += bres.dx;
			bres.y0 += bres.sy;
		}
  }
}

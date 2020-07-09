/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/10 17:04:09 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	fill_bottomflat_triangle(t_vec3d v1, t_vec3d v2, t_vec3d v3, t_sdl *sdl)
{
	float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
	float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);
	float curx1 = v1.x;
	float curx2 = v1.x;
	float scanlineY = v1.y;
	t_vec3d ve0;
	t_vec3d ve1;

	if ((int)v3.x != (int)v2.x)
	{
		ve0.x = v3.x;
		ve0.y = v2.y;
		ve1.x = v2.x;
		ve1.y = v2.y;
		drawline(ve0, ve1, sdl);
	}
	while (scanlineY <= v2.y)
	{
		ve0.x = curx1;
		ve0.y = scanlineY;
		ve1.x = curx2;
		ve1.y = scanlineY;
		drawline(ve0, ve1, sdl);
		curx1 += invslope1;
		curx2 += invslope2;
		scanlineY++;
	}
}

void	fill_topflat_triangle(t_vec3d v1, t_vec3d v2, t_vec3d v3, t_sdl *sdl)
{
	float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
	float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);
	float curx1 = v3.x;
	float curx2 = v3.x;
	float scanlineY = v3.y;
	t_vec3d ve0;
	t_vec3d ve1;

	while (scanlineY > v1.y)
	{
		ve0.x = curx1;
		ve0.y = scanlineY;
		ve1.x = curx2;
		ve1.y = scanlineY;
		drawline(ve0, ve1, sdl);
		curx1 -= invslope1;
		curx2 -= invslope2;
		scanlineY--;
	}
}

void	sort_tri_y(t_triangle *tri)
{
	if (tri->p[1].y < tri->p[0].y)
		swap_v(&tri->p[1], &tri->p[0]);
	if (tri->p[2].y < tri->p[0].y)
		swap_v(&tri->p[2], &tri->p[0]);
	if (tri->p[2].y < tri->p[1].y)
		swap_v(&tri->p[2], &tri->p[1]);
}

void	fill_triangle(t_triangle tri, t_sdl *sdl)
{
	t_triangle	n_tri;
	t_vec3d		v4;

	n_tri = tri;
	sort_tri_y(&n_tri);
	if (n_tri.p[1].y == n_tri.p[2].y)
		fill_bottomflat_triangle(n_tri.p[0], n_tri.p[1], n_tri.p[2], sdl);
	else if (n_tri.p[0].y == n_tri.p[1].y)
		fill_topflat_triangle(n_tri.p[0], n_tri.p[1], n_tri.p[2], sdl);
	else
	{
		v4.x = (n_tri.p[0].x + ((n_tri.p[1].y - n_tri.p[0].y) / (n_tri.p[2].y - n_tri.p[0].y)) * (n_tri.p[2].x - n_tri.p[0].x));
		v4.y = n_tri.p[1].y;
		fill_bottomflat_triangle(n_tri.p[0], n_tri.p[1], v4, sdl);
		fill_topflat_triangle(n_tri.p[1], v4, n_tri.p[2], sdl);
	}
}

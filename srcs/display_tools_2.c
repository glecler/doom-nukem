/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/08 19:05:45 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void draw_tri(t_sdl *sdl, t_triangle t)
{
	SDL_SetRenderDrawColor(sdl->render, t.dp * 255, t.dp * 255, t.dp * 255, 255);
	fill_triangle(t, sdl);
	SDL_SetRenderDrawColor(sdl->render, t.dp * 255, t.dp * 255, t.dp * 255, 255);
	drawline(t.p[0], t.p[1], sdl);
	drawline(t.p[1], t.p[2], sdl);
	drawline(t.p[2], t.p[0], sdl);
}

void init_plane(t_vec3d *plane)
{
	init_vec(&plane[0], 0.0f, 0.0f, 0.0f);
	init_vec(&plane[1], 1.0f, 0.0f, 0.0f);
	init_vec(&plane[2], -1.0f, 0.0f, 0.0f);
	init_vec(&plane[3], 0.0f, 1.0f, 0.0f);
	init_vec(&plane[4], 0.0f, -1.0f, 0.0f);
	init_vec(&plane[5], (float)SIZE_X - 1, 0.0f, 0.0f);
	init_vec(&plane[6], 0.0f, (float)SIZE_Y - 1, 0.0f);
}

int	clip_all_plane(int p, t_vec3d *plane, t_triangle tmp_tri, t_triangle *clipped)
{
	int nclipped;
	static int q;

	if (!q)
		q=0;
	nclipped = 0;
	if (p == 0)
		nclipped = tri_clipping(plane[0], plane[3], tmp_tri, &clipped[0], &clipped[1]);
	else if (p == 1)
		nclipped = tri_clipping(plane[5], plane[2], tmp_tri, &clipped[0], &clipped[1]);
	else if (p == 2)
		nclipped = tri_clipping(plane[0], plane[1], tmp_tri, &clipped[0], &clipped[1]);
	else if (p == 3)
		nclipped = tri_clipping(plane[6], plane[4], tmp_tri, &clipped[0], &clipped[1]);
	return(nclipped);
}

void new_clip_tri(int i, int nclipped, int *k, t_triangle *clipped, t_triangle *cpy_tri)
{
	int n;

	n = 0;
	while (n < nclipped)
	{
		cpy_tri[i + n + *k] = clipped[n];
		n++;
	}
	if (nclipped == 2)
		*k += 1;
	if (nclipped == 0)
		*k -= 1;
}

t_triangle *alloc_tri(t_triangle *tmp_tri, int d, t_triangle *cpy_tri)
{
	free(tmp_tri);
	if (!(tmp_tri = malloc(sizeof(t_triangle) * (d))))
		exit (0);
	tmp_tri = tri_memcpy(tmp_tri, cpy_tri, (size_t)d);
	return(tmp_tri);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_gen_tools_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:31:09 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

float	shade_light(t_vec3d normal, t_vec3d vcamera)
{
	t_vec3d light_direction;
	float		dp;

	init_vec(&light_direction, fabs(vcamera.x), fabs(vcamera.y), fabs(vcamera.z));
	light_direction = vec_normalise(light_direction);
	dp = fmax(0.1f, dot_product(light_direction, normal));
	return (dp);
}

t_triangle	scale_screen(t_triangle tri)
{
	t_vec3d			voffsetview;

	voffsetview.x = 1.0f;
	voffsetview.y = 1.0f;
	voffsetview.z = 0.0f;
	voffsetview.w = 1.0f;
	tri.p[0].x *= -1.0f;
	tri.p[1].x *= -1.0f;
	tri.p[2].x *= -1.0f;
	tri.p[0].y *= -1.0f;
	tri.p[1].y *= -1.0f;
	tri.p[2].y *= -1.0f;
	tri.p[0] = vec_add(tri.p[0], voffsetview);
	tri.p[1] = vec_add(tri.p[1], voffsetview);
	tri.p[2] = vec_add(tri.p[2], voffsetview);
	tri.p[0].x *= 0.5f * SIZE_X;
	tri.p[0].y *= 0.5f * SIZE_Y;
	tri.p[1].x *= 0.5f * SIZE_X;
	tri.p[1].y *= 0.5f * SIZE_Y;
	tri.p[2].x *= 0.5f * SIZE_X;
	tri.p[2].y *= 0.5f * SIZE_Y;
	return (tri);
}

void 	draw_crosshair(t_sdl *sdl)
{
	t_vec3d curs0;
	t_vec3d curs1;
	t_vec3d curs2;
	t_vec3d curs3;

	init_vec(&curs0, (float)(SIZE_X / 2 - 7), (float)(SIZE_Y / 2), 0.0f);
	init_vec(&curs1, (float)(SIZE_X / 2 + 7), (float)(SIZE_Y / 2), 0.0f);
	init_vec(&curs2, (float)(SIZE_X / 2), (float)(SIZE_Y / 2 - 7), 0.0f);
	init_vec(&curs3, (float)(SIZE_X / 2), (float)(SIZE_Y / 2 + 7), 0.0f);
	SDL_SetRenderDrawColor(sdl->render, 230, 0, 172, 255);
	drawline(curs0, curs1, sdl);
	drawline(curs2, curs3, sdl);
}

t_triangle trans_mat(t_triangle tri_trans, t_world *world, t_env *env)
{
	tri_trans.p[0] = mat_mulvec(world->matworld, env->tri[world->i].p[0]);
	tri_trans.p[1] = mat_mulvec(world->matworld, env->tri[world->i].p[1]);
	tri_trans.p[2] = mat_mulvec(world->matworld, env->tri[world->i].p[2]);
	tri_trans.index = env->tri[world->i].index;
	tri_trans.t[0] = env->tri[world->i].t[0];
	tri_trans.t[1] = env->tri[world->i].t[1];
	tri_trans.t[2] = env->tri[world->i].t[2];
	world->normal = calc_normal(world->normal, tri_trans);
	world->vcam_ray = vec_sub(tri_trans.p[0], env->vcamera);
	return (tri_trans);
}

t_triangle	world_to_view(t_triangle t_trs, t_triangle t_vw, t_world world)
{
	t_vw.p[0] = mat_mulvec(world.matview, t_trs.p[0]);
	t_vw.p[1] = mat_mulvec(world.matview, t_trs.p[1]);
	t_vw.p[2] = mat_mulvec(world.matview, t_trs.p[2]);
	t_vw.index = t_trs.index;
	t_vw.t[0] = t_trs.t[0];
	t_vw.t[1] = t_trs.t[1];
	t_vw.t[2] = t_trs.t[2];
	return (t_vw);
}

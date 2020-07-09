/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/04 13:38:36 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

// struct var
t_vec3d vec_intersec_plane(t_vec3d plane_p, t_vec3d plane_n, t_vec3d lineStart, t_vec3d lineEnd, float *t)
{
	float plane_d;
	float ad;
	float bd;
	t_vec3d lineStartToEnd;
	t_vec3d lineToIntersect;

	plane_n = vec_normalise(plane_n);
	plane_d = -dot_product(plane_n, plane_p);
	ad = dot_product(lineStart, plane_n);
	bd = dot_product(lineEnd, plane_n);
	*t = (-plane_d - ad) / (bd - ad);
	lineStartToEnd = vec_sub(lineEnd, lineStart);
	lineToIntersect = vec_mul(lineStartToEnd, *t);
	return (vec_add(lineStart, lineToIntersect));
}

float dist(t_vec3d p, t_vec3d plane_n, t_vec3d plane_p)
{
	float		x;

	x = dot_product(plane_n, p) - dot_product(plane_n, plane_p);
  return (x);
}

// struct var + norme
int tri_clipping(t_vec3d plane_p, t_vec3d plane_n, t_triangle in_tri, t_triangle *out_tri1, t_triangle *out_tri2)
{
  t_vec3d in_points[3];
  t_vec3d out_points[3];
  int     in_pc;
  int     out_pc;
	t_vec2d in_tex[3];
	t_vec2d out_tex[3];
	int in_tc;
	int out_tc;
  float   d0;
  float   d1;
  float   d2;
	float t;
  plane_n = vec_normalise(plane_n);
	t = 0;
  out_pc = 0;
  in_pc = 0;
	out_tc = 0;
	in_tc = 0;
	d0 = dist(in_tri.p[0], plane_n, plane_p);
	d1 = dist(in_tri.p[1], plane_n, plane_p);
	d2 = dist(in_tri.p[2], plane_n, plane_p);
	if (d0 >= 0)
	{
		in_points[in_pc++] = in_tri.p[0];
		in_tex[in_tc++] = in_tri.t[0];
	}
	else
	{
		out_points[out_pc++] = in_tri.p[0];
		out_tex[out_tc++] = in_tri.t[0];
	}
	if (d1 >= 0)
	{
		in_points[in_pc++] = in_tri.p[1];
		in_tex[in_tc++] = in_tri.t[1];
	}
	else
	{
		out_points[out_pc++] = in_tri.p[1];
		out_tex[out_tc++] = in_tri.t[1];
	}
	if (d2 >= 0)
	{
		in_points[in_pc++] = in_tri.p[2];
		in_tex[in_tc++] = in_tri.t[2];
	}
	else
	{
		out_points[out_pc++] = in_tri.p[2];
		out_tex[out_tc++] = in_tri.t[2];
	}
	if (in_pc == 0)
		return (0);
	if (in_pc == 3)
  {
		*out_tri1 = in_tri;
		return (1);
	}
	if (in_pc == 1 && out_pc == 2)
	{
		out_tri1->p[0] = in_points[0];
		out_tri1->t[0] = in_tex[0];
		out_tri1->p[1] = vec_intersec_plane(plane_p, plane_n, in_points[0], out_points[0], &t);
  	out_tri1->t[1].u = t * (out_tex[0].u - in_tex[0].u) + in_tex[0].u;
		out_tri1->t[1].v = t * (out_tex[0].v - in_tex[0].v) + in_tex[0].v;
		out_tri1->t[1].w = t * (out_tex[0].w - in_tex[0].w) + in_tex[0].w;
		out_tri1->p[2] = vec_intersec_plane(plane_p, plane_n, in_points[0], out_points[1], &t);
		out_tri1->t[2].u = t * (out_tex[1].u - in_tex[0].u) + in_tex[0].u;
		out_tri1->t[2].v = t * (out_tex[1].v - in_tex[0].v) + in_tex[0].v;
		out_tri1->t[2].w = t * (out_tex[1].w - in_tex[0].w) + in_tex[0].w;
		out_tri1->dp = in_tri.dp;
		out_tri1->index = in_tri.index;
		return (1);
	}
	if (in_pc == 2 && out_pc == 1)
	{
		out_tri1->p[0] = in_points[0];
		out_tri1->p[1] = in_points[1];
		out_tri1->t[0] = in_tex[0];
		out_tri1->t[1] = in_tex[1];
		out_tri1->p[2] = vec_intersec_plane(plane_p, plane_n, in_points[0], out_points[0], &t);
		out_tri1->t[2].u =  t * (out_tex[0].u - in_tex[0].u) + in_tex[0].u;
		out_tri1->t[2].v = t * (out_tex[0].v - in_tex[0].v) + in_tex[0].v;
		out_tri1->t[2].w = t * (out_tex[0].w - in_tex[0].w) + in_tex[0].w;

		out_tri2->p[0] = in_points[1];
		out_tri2->t[0] = in_tex[1];
		out_tri2->p[1] = out_tri1->p[2];
		out_tri2->t[1] = out_tri1->t[2];
		out_tri2->p[2] = vec_intersec_plane(plane_p, plane_n, in_points[1], out_points[0], &t);
		out_tri2->t[2].u = t * (out_tex[0].u - in_tex[1].u) + in_tex[1].u;
		out_tri2->t[2].v = t * (out_tex[0].v - in_tex[1].v) + in_tex[1].v;
		out_tri2->t[2].w = t * (out_tex[0].w - in_tex[1].w) + in_tex[1].w;
		out_tri1->dp = in_tri.dp;
		out_tri2->dp = in_tri.dp;
		out_tri1->index = in_tri.index;
		out_tri2->index = in_tri.index;
		return (2);
	}
  return (-1);
}

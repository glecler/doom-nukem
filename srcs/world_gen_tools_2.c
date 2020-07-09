/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_gen_tools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:31:09 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_triangle projection(t_triangle tri_proj, t_clipz clipz, t_env *env)
{
  tri_proj.p[0] = mat_mulvec(env->matproj, clipz.clipped[clipz.n].p[0]);
  tri_proj.p[1] = mat_mulvec(env->matproj, clipz.clipped[clipz.n].p[1]);
  tri_proj.p[2] = mat_mulvec(env->matproj, clipz.clipped[clipz.n].p[2]);
  tri_proj.dp = clipz.color;
  tri_proj.index = clipz.clipped[clipz.n].index;
  tri_proj.t[0] = clipz.clipped[clipz.n].t[0];
  tri_proj.t[1] = clipz.clipped[clipz.n].t[1];
  tri_proj.t[2] = clipz.clipped[clipz.n].t[2];
  tri_proj.t[0].u = tri_proj.t[0].u / tri_proj.p[0].w;
  tri_proj.t[1].u = tri_proj.t[1].u / tri_proj.p[1].w;
  tri_proj.t[2].u = tri_proj.t[2].u / tri_proj.p[2].w;
  tri_proj.t[0].v = tri_proj.t[0].v / tri_proj.p[0].w;
  tri_proj.t[1].v = tri_proj.t[1].v / tri_proj.p[1].w;
  tri_proj.t[2].v = tri_proj.t[2].v / tri_proj.p[2].w;
  tri_proj.t[0].w = 1.0f / tri_proj.p[0].w;
  tri_proj.t[1].w = 1.0f / tri_proj.p[1].w;
  tri_proj.t[2].w = 1.0f / tri_proj.p[2].w;
  tri_proj.p[0] = vec_div(tri_proj.p[0], tri_proj.p[0].w);
  tri_proj.p[1] = vec_div(tri_proj.p[1], tri_proj.p[1].w);
  tri_proj.p[2] = vec_div(tri_proj.p[2], tri_proj.p[2].w);
  return (tri_proj);
}

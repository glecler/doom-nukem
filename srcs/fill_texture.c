/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/10 17:04:09 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

// couper pour norme et Fix petit trait mayB vérif step X
void  fill_texture(t_triangle tri, t_texture tex, t_depth *depth)
{
  t_tex_var var;
  int i;
  int j;

  var.ax = 0;
  if (tri.p[1].y < tri.p[0].y)
  {
    swap_v(&tri.p[1], &tri.p[0]);
    swap_v2(&tri.t[1], &tri.t[0]);
  }
	if (tri.p[2].y < tri.p[0].y)
  {
    swap_v(&tri.p[2], &tri.p[0]);
    swap_v2(&tri.t[2], &tri.t[0]);

  }
	if (tri.p[2].y < tri.p[1].y)
  {
    swap_v(&tri.p[2], &tri.p[1]);
    swap_v2(&tri.t[2], &tri.t[1]);
  }
  var = init_tex_var(tri, var);
  var = get_step(var);
	if (var.dy1)
	{
    i = tri.p[0].y + 1; // vire quelque trait
    if (i < 0)
      i = 0;
    if (tri.p[1].y >= 600)
      tri.p[1].y = 599;
		while (i < tri.p[1].y)
		{
			var.ax = tri.p[0].x + (float)(i - tri.p[0].y) * var.dax_step;
			var.bx = tri.p[0].x + (float)(i - tri.p[0].y) * var.dbx_step;
			var.tex_su = tri.t[0].u + (float)(i - tri.p[0].y) * var.du1_step;
			var.tex_sv = tri.t[0].v + (float)(i - tri.p[0].y) * var.dv1_step;
			var.tex_sw = tri.t[0].w + (float)(i - tri.p[0].y) * var.dw1_step;

			var.tex_eu = tri.t[0].u + (float)(i - tri.p[0].y) * var.du2_step;
			var.tex_ev = tri.t[0].v + (float)(i - tri.p[0].y) * var.dv2_step;
			var.tex_ew = tri.t[0].w + (float)(i - tri.p[0].y) * var.dw2_step;

			if (var.ax > var.bx)
			{
				swap_i(&var.ax, &var.bx);
				swap_f(&var.tex_su, &var.tex_eu);
				swap_f(&var.tex_sv, &var.tex_ev);
				swap_f(&var.tex_sw, &var.tex_ew);
			}

			var.tex_u = var.tex_su;
			var.tex_v = var.tex_sv;
			var.tex_w = var.tex_sw;

			var.tstep = 1.0f / ((float)(var.bx - var.ax));
			var.t = 0.0f;
      j = var.ax;
      if (j < 0)
        j = 0;
      if (var.bx >= 800)
        var.bx = 799;
			while (j <= var.bx) // = plus de trait ?
			{
				var.tex_u = (1.0f - var.t) * var.tex_su + var.t * var.tex_eu;
				var.tex_v = (1.0f - var.t) * var.tex_sv + var.t * var.tex_ev;
				var.tex_w = (1.0f - var.t) * var.tex_sw + var.t * var.tex_ew;
				if (var.tex_w > depth[i * SIZE_X + j].w)
				{
          var.tex_x = (int)(var.tex_u / var.tex_w * tex.x);
          var.tex_y = (int)(var.tex_v / var.tex_w * tex.y);
          var.tex_x = (var.tex_x < 0) ? 0 : var.tex_x;
          var.tex_y = (var.tex_y < 0) ? 0 : var.tex_y;
          var.tex_x = (var.tex_x >= tex.x) ? tex.x - 1 : var.tex_x;
          var.tex_y = (var.tex_y >= tex.y) ? tex.y - 1 : var.tex_y;
          if(tex.alphas[var.tex_y][var.tex_x] != 0)
          {
            depth[i * SIZE_X + j].w = var.tex_w;
            depth[i * SIZE_X + j].color = tex.pixels[var.tex_y][var.tex_x];
          }
				}
				var.t += var.tstep;
        j++;
			}
      i++;
		}
	}
	var = init_tex_var_second(tri, var);
	if (var.dy1)
	{
    i = tri.p[1].y;
    if (i < 0)
      i = 0;
    if (tri.p[2].y >= 600)
      tri.p[2].y = 599;
		while (i < tri.p[2].y) // = plus de trait ?
		{
			var.ax = tri.p[1].x + (float)(i - tri.p[1].y) * var.dax_step;
			var.bx = tri.p[0].x + (float)(i - tri.p[0].y) * var.dbx_step;
			var.tex_su = tri.t[1].u + (float)(i - tri.p[1].y) * var.du1_step;
			var.tex_sv = tri.t[1].v + (float)(i - tri.p[1].y) * var.dv1_step;
			var.tex_sw = tri.t[1].w + (float)(i - tri.p[1].y) * var.dw1_step;

			var.tex_eu = tri.t[0].u + (float)(i - tri.p[0].y) * var.du2_step;
			var.tex_ev = tri.t[0].v + (float)(i - tri.p[0].y) * var.dv2_step;
			var.tex_ew = tri.t[0].w + (float)(i - tri.p[0].y) * var.dw2_step;
			if (var.ax > var.bx)
			{
				swap_i(&var.ax, &var.bx);
				swap_f(&var.tex_su, &var.tex_eu);
				swap_f(&var.tex_sv, &var.tex_ev);
				swap_f(&var.tex_sw, &var.tex_ew);
			}

			var.tex_u = var.tex_su;
			var.tex_v = var.tex_sv;
			var.tex_w = var.tex_sw;

			var.tstep = 1.0f / ((float)(var.bx - var.ax));
			var.t = 0.0f;
      j = var.ax;
      if (j < 0)
        j = 0;
      if (var.bx >= 800)
        var.bx = 799;
			while (j < var.bx)
			{
				var.tex_u = (1.0f - var.t) * var.tex_su + var.t * var.tex_eu;
				var.tex_v = (1.0f - var.t) * var.tex_sv + var.t * var.tex_ev;
				var.tex_w = (1.0f - var.t) * var.tex_sw + var.t * var.tex_ew;
				if (var.tex_w > depth[i * SIZE_X + j].w)
				{
          var.tex_x = (int)(var.tex_u / var.tex_w * tex.x);
          var.tex_y = (int)(var.tex_v / var.tex_w * tex.y);
          var.tex_x = (var.tex_x < 0) ? 0 : var.tex_x;
          var.tex_y = (var.tex_y < 0) ? 0 : var.tex_y;
          var.tex_x = (var.tex_x >= tex.x) ? tex.x - 1 : var.tex_x;
          var.tex_y = (var.tex_y >= tex.y) ? tex.y - 1 : var.tex_y;
          if(tex.alphas[var.tex_y][var.tex_x] != 0)
          {
            depth[i * SIZE_X + j].w = var.tex_w;
            depth[i * SIZE_X + j].color = tex.pixels[var.tex_y][var.tex_x];
          }
				}
				var.t += var.tstep;
        j++;
			}
      i++;
		}
	}
}

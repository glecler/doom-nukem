/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture_tools_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/10 17:04:09 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_tex_var init_tex_var(t_triangle tri, t_tex_var var)
{
  var.dy1 = tri.p[1].y - tri.p[0].y;
	var.dx1 = tri.p[1].x - tri.p[0].x;
	var.dv1 = tri.t[1].v - tri.t[0].v;
	var.du1 = tri.t[1].u - tri.t[0].u;
	var.dw1 = tri.t[1].w - tri.t[0].w;
	var.dy2 = tri.p[2].y - tri.p[0].y;
	var.dx2 = tri.p[2].x - tri.p[0].x;
	var.dv2 = tri.t[2].v - tri.t[0].v;
	var.du2 = tri.t[2].u - tri.t[0].u;
	var.dw2 = tri.t[2].w - tri.t[0].w;
  var.dax_step = 0;
  var.dbx_step = 0;
  var.du1_step = 0;
  var.dv1_step = 0;
  var.du2_step = 0;
  var.dv2_step = 0;
	var.dw1_step = 0;
  var.dw2_step = 0;
  return (var);
}

t_tex_var get_step(t_tex_var var)
{
  if (var.dy1)
    var.dax_step = var.dx1 / (float)abs(var.dy1);
	if (var.dy2)
    var.dbx_step = var.dx2 / (float)abs(var.dy2);
	if (var.dy1)
    var.du1_step = var.du1 / (float)abs(var.dy1);
	if (var.dy1)
    var.dv1_step = var.dv1 / (float)abs(var.dy1);
	if (var.dy1)
    var.dw1_step = var.dw1 / (float)abs(var.dy1);
	if (var.dy2)
    var.du2_step = var.du2 / (float)abs(var.dy2);
	if (var.dy2)
    var.dv2_step = var.dv2 / (float)abs(var.dy2);
	if (var.dy2)
    var.dw2_step = var.dw2 / (float)abs(var.dy2);
  return (var);
}

t_tex_var init_tex_var_second(t_triangle tri, t_tex_var var)
{
  var.dy1 = tri.p[2].y - tri.p[1].y;
	var.dx1 = tri.p[2].x - tri.p[1].x;
	var.dv1 = tri.t[2].v - tri.t[1].v;
	var.du1 = tri.t[2].u - tri.t[1].u;
	var.dw1 = tri.t[2].w - tri.t[1].w;
  var.du1_step = 0;
  var.dv1_step = 0;
	if (var.dy1)
    var.dax_step = var.dx1 / (float)abs(var.dy1);
	if (var.dy2)
    var.dbx_step = var.dx2 / (float)abs(var.dy2);
	if (var.dy1)
    var.du1_step = var.du1 / (float)abs(var.dy1);
	if (var.dy1)
    var.dv1_step = var.dv1 / (float)abs(var.dy1);
	if (var.dy1)
    var.dw1_step = var.dw1 / (float)abs(var.dy1);
  return (var);
}

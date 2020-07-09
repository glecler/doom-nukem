/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/03 17:13:02 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

float dot_product(t_vec3d v1, t_vec3d v2)
{
  return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float vec_len(t_vec3d v1)
{
  return (sqrtf(dot_product(v1, v1)));
}

t_vec3d vec_normalise(t_vec3d v1)
{
  float l;
  t_vec3d n_vec;

  l = vec_len(v1);
  n_vec.x = v1.x / l;
  n_vec.y = v1.y / l;
  n_vec.z = v1.z / l;
  n_vec.w = 1.0f;
  return (n_vec);
}

t_vec3d cross_product(t_vec3d v1, t_vec3d v2)
{
  t_vec3d n_vec;

  n_vec.x = v1.y * v2.z - v1.z * v2.y;
  n_vec.y = v1.z * v2.x - v1.x * v2.z;
  n_vec.z = v1.x * v2.y - v1.y * v2.x;
  n_vec.w = 1.0f;
  return(n_vec);
}

t_vec3d	calc_normal(t_vec3d normal, t_triangle tri_trans)
{
	t_vec3d line1;
	t_vec3d line2;

	line1 = vec_sub(tri_trans.p[1], tri_trans.p[0]);
	line2 = vec_sub(tri_trans.p[2], tri_trans.p[0]);
	normal = cross_product(line1, line2);
	normal = vec_normalise(normal);
	return (normal);
}

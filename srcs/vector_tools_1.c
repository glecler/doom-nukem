/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/23 17:20:43 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_vec3d vec_add(t_vec3d v1, t_vec3d v2)
{
  t_vec3d n_vec;

  n_vec.x = v1.x + v2.x;
  n_vec.y = v1.y + v2.y;
  n_vec.z = v1.z + v2.z;
  n_vec.w = 1.0f;
  return (n_vec);
}

t_vec3d vec_sub(t_vec3d v1, t_vec3d v2)
{
  t_vec3d n_vec;

  n_vec.x = v1.x - v2.x;
  n_vec.y = v1.y - v2.y;
  n_vec.z = v1.z -  v2.z;
  n_vec.w = 1.0f;
    return (n_vec);
}

t_vec3d vec_mul(t_vec3d v1, float k)
{
  v1.x *= k;
  v1.y *= k;
  v1.z *= k;
    return (v1);
}

t_vec3d vec_div(t_vec3d v1, float k)
{
  v1.x /= k;
  v1.y /= k;
  v1.z /= k;
    return (v1);
}

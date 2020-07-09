/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser_tools_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:09:55 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void 	get_spawn(t_env *env, char *str)
{
	int i;

	i = 5;
	i = skip(str, i);
	env->vcamera.x = ft_atof(str + i);
	i = skip(str, i);
	env->vcamera.y = ft_atof(str + i);
	i = skip(str, i);
	env->vcamera.z = ft_atof(str + i);
	env->spawn = env->vcamera;
}

t_obb *obb_memcpy(t_obb *dest, t_obb *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

t_obb *obb_add_size(t_obb *data, int size)
{
	t_obb	*cpy;

	if (!(cpy = malloc(sizeof(t_obb) * (4096 * size))))
		exit (0);
	if (size > 1)
		cpy = obb_memcpy(cpy, data, 4096 * (size - 1));
	free(data);
	return (cpy);
}

// refaire fonction pour OBB et pas AABB
t_obb p_obb(t_obb obb, t_triangle *tri, int nb, int first)
{
  int i;
  int j;
  float min[3];
  float max[3];

  i = -1;
  min[0] = tri[0].p[0].x;
  min[1] = tri[0].p[0].y;
  min[2] = tri[0].p[0].z;
  max[0] = tri[0].p[0].x;
  max[1] = tri[0].p[0].y;
  max[2] = tri[0].p[0].z;
  while (++i < nb)
  {
    j = -1;
    while (++j < 3)
    {
      min[0] = (tri[i].p[j].x < min[0]) ? tri[i].p[j].x : min[0];
      min[1] = (tri[i].p[j].y < min[1]) ? tri[i].p[j].y : min[1];
      min[2] = (tri[i].p[j].z < min[2]) ? tri[i].p[j].z : min[2];
      max[0] = (tri[i].p[j].x > max[0]) ? tri[i].p[j].x : max[0];
      max[1] = (tri[i].p[j].y > max[1]) ? tri[i].p[j].y : max[1];
      max[2] = (tri[i].p[j].z > max[2]) ? tri[i].p[j].z : max[2];
    }
  }
  obb.halfsize.x = (max[0] - min[0]) / 2;
  obb.halfsize.y = (max[1] - min[1]) / 2;
  obb.halfsize.z = (max[2] - min[2]) / 2;
	obb.halfsize.w = 1.0f;

  obb.center.x = min[0] + obb.halfsize.x;
  obb.center.y = min[1] + obb.halfsize.y;
  obb.center.z = min[2] + obb.halfsize.z;
	obb.center.w = 1.0f;
	if (obb.id == 3)
	{
		obb.halfsize.x -= 1.7;
		obb.halfsize.y -= 1.7;
		obb.halfsize.z -= 1.7;
	}
	obb.halfsize.x += 3;
	obb.halfsize.y += 3;
	obb.halfsize.z += 3;
	obb.last = nb + first;
	obb.first = obb.last - nb;
  return(obb);
}

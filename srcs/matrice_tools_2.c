/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/24 17:10:12 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_mat4x4  mat_makeid(void)
{
  t_mat4x4  m;

  init_mat_zero(&m);
  m.m[0][0] = 1.0f;
  m.m[1][1] = 1.0f;
  m.m[2][2] = 1.0f;
  m.m[3][3] = 1.0f;
  return (m);
}

t_mat4x4  mat_maketrans(float x, float y, float z)
{
	t_mat4x4 m;

  init_mat_zero(&m);
	m.m[0][0] = 1.0f;
	m.m[1][1] = 1.0f;
	m.m[2][2] = 1.0f;
	m.m[3][3] = 1.0f;
	m.m[3][0] = x;
	m.m[3][1] = y;
	m.m[3][2] = z;
	return (m);
}

t_mat4x4  mat_makeproj(float fFov, float fAspectRatio, float fNear, float fFar)
{
	t_mat4x4 m;
	float	fFovRad;

	init_mat_zero(&m);
	fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
	m.m[0][0] =  fAspectRatio * fFovRad;
	m.m[1][1] = fFovRad;
	m.m[2][2] = fFar / (fFar - fNear);
	m.m[2][3] = 1.0f;
	m.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	m.m[3][3] = 0.0f;
	return (m);
}

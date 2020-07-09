/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_tools_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/22 17:13:43 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_vec3d mat_mulvec(t_mat4x4 m, t_vec3d i)
{
	t_vec3d v;
	v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
	v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
	v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
	v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
	return v;
}

t_mat4x4 mat_multmat(t_mat4x4 m1, t_mat4x4 m2)
{
	t_mat4x4 m;
	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++)
			m.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
	return (m);
}

// Struct VAR-Norme
t_mat4x4  mat_pointat(t_vec3d pos, t_vec3d target, t_vec3d up)
{
	t_vec3d newforward;
	t_vec3d a;
	t_vec3d newup;
	t_vec3d newright;
	t_mat4x4 m;
	newforward = vec_sub(target, pos);
	newforward = vec_normalise(newforward);
	a = vec_mul(newforward, dot_product(up, newforward));
	newup = vec_sub(up, a);
	newup = vec_normalise(newup);
  newright = cross_product(newup, newforward);
	m.m[0][0] = newright.x;
	m.m[0][1] = newright.y;
	m.m[0][2] = newright.z;
	m.m[0][3] = 0.0f;
	m.m[1][0] = newup.x;
	m.m[1][1] = newup.y;
	m.m[1][2] = newup.z;
	m.m[1][3] = 0.0f;
	m.m[2][0] = newforward.x;
	m.m[2][1] = newforward.y;
	m.m[2][2] = newforward.z;
	m.m[2][3] = 0.0f;
	m.m[3][0] = pos.x;
	m.m[3][1] = pos.y;
	m.m[3][2] = pos.z;
	m.m[3][3] = 1.0f;
	return (m);
}

t_mat4x4  mat_quick_invert(t_mat4x4 m)
{
		t_mat4x4 m1;

		m1.m[0][0] = m.m[0][0];
		m1.m[0][1] = m.m[1][0];
		m1.m[0][2] = m.m[2][0];
		m1.m[0][3] = 0.0f;
		m1.m[1][0] = m.m[0][1];
		m1.m[1][1] = m.m[1][1];
		m1.m[1][2] = m.m[2][1];
		m1.m[1][3] = 0.0f;
		m1.m[2][0] = m.m[0][2];
		m1.m[2][1] = m.m[1][2];
		m1.m[2][2] = m.m[2][2];
		m1.m[2][3] = 0.0f;
		m1.m[3][0] = -(m.m[3][0] * m1.m[0][0] + m.m[3][1] * m1.m[1][0] + m.m[3][2] * m1.m[2][0]);
		m1.m[3][1] = -(m.m[3][0] * m1.m[0][1] + m.m[3][1] * m1.m[1][1] + m.m[3][2] * m1.m[2][1]);
		m1.m[3][2] = -(m.m[3][0] * m1.m[0][2] + m.m[3][1] * m1.m[1][2] + m.m[3][2] * m1.m[2][2]);
		m1.m[3][3] = 1.0f;
		return (m1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_tools_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/23 17:20:43 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	init_mat_zero(t_mat4x4 *mat)
{
	int	x;
	int	y;

	x = -1;
	while (++x < 4)
	{
		y = -1;
		while (++y < 4)
			mat->m[x][y] = 0.0f;
	}
}

t_mat4x4	init_matrotx(float fTheta)
{
	t_mat4x4	m;

	init_mat_zero(&m);
	m.m[0][0] = 1.0f;
	m.m[1][1] = cosf(fTheta);
	m.m[1][2] = sinf(fTheta);
	m.m[2][1] = -sinf(fTheta);
	m.m[2][2] = cosf(fTheta);
	m.m[3][3] = 1.0f;
	return (m);
}

t_mat4x4	init_matroty(float fTheta)
{
	t_mat4x4 m;

	init_mat_zero(&m);
	m.m[0][0] = cosf(fTheta);
	m.m[0][2] = sinf(fTheta);
	m.m[2][0] = -sinf(fTheta);
	m.m[1][1] = 1.0f;
	m.m[2][2] = cosf(fTheta);
	m.m[3][3] = 1.0f;
	return (m);
}

t_mat4x4	init_matrotz(float fTheta)
{
	t_mat4x4	m;

	init_mat_zero(&m);
	m.m[0][0] = cosf(fTheta);
	m.m[0][1] = sinf(fTheta);
	m.m[1][0] = -sinf(fTheta);
	m.m[1][1] = cosf(fTheta);
	m.m[2][2] = 1.0f;
	m.m[3][3] = 1.0f;
	return (m);
}

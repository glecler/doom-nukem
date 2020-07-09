/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void texture_item(t_env *env, t_obb obb, int j)
{
	int i;

	i = obb.first;
	while (i <= obb.last)
	{
		env->tri[i].index = env->nb_tex - j;
		i++;
	}
}

void texture_portal2(t_obb *obb, t_env *env)
{
	int i;
	int q;

	i = 0;
	while (obb[i].id != 6)
		i++;
	q = obb[i].first;
	while (q <= obb[i].last)
	{
		env->tri[q].index = env->nb_tex - 14;
		q++;
	}
}

void texture_portal(t_obb *obb, t_env *env)
{
	int i;
	int q;

	i = 0;
	while (obb[i].id != 6)
		i++;
	q = obb[i].first;
	while (q <= obb[i].last)
	{
		env->tri[q].index = env->nb_tex - 13;
		q++;
	}
}

int 	hit(t_vec3d tir, t_obb *obb, int borne, t_env *env)
{
	int i;
	t_vec3d max;
	t_vec3d min;
	float		*data_vec;

	if (!(data_vec = malloc(sizeof(float) * 6)))
		exit (0);
	i = 0;
	while (i <= borne)
	{
		obb[i].halfsize.x -= 1; //peut etre 3 ici, check hitbox needed mayB if id = 0
		obb[i].halfsize.y -= 1;
		obb[i].halfsize.z -= 1;
		init_col(data_vec, obb[i].center, obb[i].halfsize);
		obb[i].halfsize.x += 1;
		obb[i].halfsize.y += 1;
		obb[i].halfsize.z += 1;
		init_vec(&max, data_vec[0], data_vec[1], data_vec[2]);
		init_vec(&min, data_vec[3], data_vec[4], data_vec[5]);
		if (tir.x >= min.x && tir.y >= min.y && tir.z >= min.z && tir.x <= max.x &&\
			 tir.y <= max.y && tir.z <= max.z)
		{
			if (obb[i].id == 5)
			{
				texture_item(env, obb[i], 12);
				obb[i].id = -1;
				env->end++;
			}
			if (obb[i].id == 4)
			{
				printf("tourelle\n");
				vanish_item(env, obb[i]);
				obb[i].id = -3;
			}
			else if (obb[i].id == 3)
				printf("AIE\n");
			free(data_vec);
			return(1);
		}
		i++;
	}
	free(data_vec);
	return (0);
}

// Make fun lines
void 	shoot(t_env *env)
{
	t_vec3d tir;
	t_vec3d dtir;

	tir.x = -(cos(env->fpitch) * sin(env->fyaw));
	tir.y = sin(-env->fpitch);
	tir.z = cos(env->fpitch) * cos(env->fyaw);
	tir.w = 0.0f;
	dtir = vec_add(tir, env->vcamera);
	while (hit(dtir, env->obb, env->nb_obb, env) == 0)
		dtir = vec_add(dtir, tir);
	if (env->end == 6)
	{
		texture_portal(env->obb, env);
		env->end++;
	}
}

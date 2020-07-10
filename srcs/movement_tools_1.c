/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_tools_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void 	init_col(float *data_vec, t_vec3d cent, t_vec3d half)
{
	data_vec[0] = cent.x + half.x;
	data_vec[1] = cent.y + half.y;
	data_vec[2] = cent.z + half.z;
	data_vec[3] = cent.x - half.x;
	data_vec[4] = cent.y - half.y;
	data_vec[5] = cent.z - half.z;
}

void vanish_item(t_env *env, t_obb obb)
{
	int i;

	i = obb.first;
	while (i <= obb.last)
	{
		env->tri[i].index = env->nb_tex - 1;
		i++;
	}
}

float ft_dist(t_vec3d a, t_vec3d b)
{
    return (sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2) + pow((b.z - a.z), 2)));
}

float ft_get_area_triangles(t_triangle tri)
{
    float a;
    float b;
    float c;
    float s;

    a = ft_dist(tri.p[0], tri.p[1]);
    b = ft_dist(tri.p[1], tri.p[2]);
    c = ft_dist(tri.p[2], tri.p[0]);
    s = (a + b + c) / 2;
    return (sqrt(s * (s - a) * (s - b) * (s - c)));
}

float ft_get_area_3_triangles(t_triangle *triangles)
{
	float ret;

	ret = 0;
    ret += ft_get_area_triangles(triangles[0]);
    ret += ft_get_area_triangles(triangles[1]);
	ret += ft_get_area_triangles(triangles[2]);
    return (ret);
}

t_triangle *ft_create_triangles(t_triangle *triangles, t_triangle triangle, t_vec3d cam)
{
    triangles[0].p[0] = triangle.p[0];
    triangles[0].p[1] = triangle.p[1];
    triangles[0].p[2] = cam;
    triangles[1].p[0] = triangle.p[1];
    triangles[1].p[1] = triangle.p[2];
    triangles[1].p[2] = cam;
    triangles[2].p[0] = triangle.p[2];
    triangles[2].p[1] = triangle.p[0];
    triangles[2].p[2] = cam;
    return (triangles);
}

int check_slope(t_env *env, t_vec3d cam, int flag, t_obb obb)
{
    int i;
	float area;
	float big_area;
    t_triangle triangles[3];

    i = obb.first;
    while (i <= obb.last)
    {
		triangles[0].p[0] = env->tri[i].p[0];
    	triangles[0].p[1] = env->tri[i].p[1];
    	triangles[0].p[2] = cam;
    	triangles[1].p[0] = env->tri[i].p[1];
    	triangles[1].p[1] = env->tri[i].p[2];
    	triangles[1].p[2] = cam;
    	triangles[2].p[0] = env->tri[i].p[2];
    	triangles[2].p[1] = env->tri[i].p[0];
    	triangles[2].p[2] = cam;
		big_area = ft_get_area_3_triangles(triangles);
		area = ft_get_area_triangles(env->tri[i]);
        if (big_area > area && big_area < (area + (20 * area / 100)))
			return (1);
		i++;
    }
    return (0);
}

int collide(t_env *env, t_vec3d cam, int flag, float speed)
{
	int i;
	float		*data_vec;
	t_vec3d max;
	t_vec3d min;

	i = -1;
	if (!(data_vec = malloc(sizeof(float) * 6)))
		exit (0);
	if (flag == 1)
		cam.y -= speed;
	else if (flag == 2)
		cam.y += speed;
	while (++i <= env->nb_obb)
	{
		if (env->obb[i].id == -1)
			i++;
		init_col(data_vec, env->obb[i].center, env->obb[i].halfsize);
		init_vec(&max, data_vec[0], data_vec[1], data_vec[2]);
		init_vec(&min, data_vec[3], data_vec[4], data_vec[5]);
		if (flag == 3)
			min.y += 2;
		if (cam.x >= min.x && cam.y >= min.y && cam.z >= min.z && cam.x <= max.x &&\
			 cam.y <= max.y && cam.z <= max.z)
		{
			if (env->obb[i].id == 1)
			{
				vanish_item(env, env->obb[i]);
				env->obb[i].id = -1;
				env->r_hp = 1;
			}
			else if (env->obb[i].id == 2) //Chnager sdl.x && sdl.y à 0
			{
				env->vcamera = env->spawn;
				env->dy = 1;
				env->hp = 20;
				env->nrj = 100;
			}
			else if (env->obb[i].id == 6 && env->end >= 7) //hitbox portal degeu
				env->fin = 1;
			if (env->obb[i].id != 7 && env->obb[i].id != 8)
			{
				free(data_vec);
				return(1);
			}
			if (env->obb[i].id == 7)
			{
				if (check_slope(env, cam, flag, env->obb[i]) == 1)
				{
					//env->vcamera.y += 0.07f;
					return(1);
				}
			}
			if (env->obb[i].id == 8)
			{
				if (check_slope(env, cam, flag, env->obb[i]) == 1)
				{
					//env->vcamera.y -= 0.3f;
					return(1);
				}
			}
		}
	}
	free(data_vec);
	return (0);
}

void crouching(t_env *env, t_move *move, const Uint8 *keys)
{
  if (move->crouch == 1 && move->jump == 0)
  {
    env->crunch = 0.8f;
    move->crouch = 2;
		move->flag = 3;
    move->velocity = 0.3f;
  }
  else if (move->crouch == 2 && keys[SDL_SCANCODE_C] == 0 && collide(env, env->vcamera, 2, move->dy) == 0)
  {
    env->crunch = 0;
    move->crouch = 0;
		move->flag = 0;
    move->velocity = 1.0f;
  }
}

void 	fly(t_env *env, t_move *move, const Uint8 *keys)
{
	t_vec3d vright;
	t_vec3d vforward;

	vright = vec_mul(env->vlookright, move->speed * move->velocity);
	vforward = vec_mul(env->vlookdir, move->speed * move->velocity);
	if (keys[SDL_SCANCODE_SPACE] == 1)
		env->vcamera.y += move->speed;
	if (keys[SDL_SCANCODE_C] == 1)
		env->vcamera.y -= move->speed;
	if (keys[SDL_SCANCODE_W] == 1)
			env->vcamera = vec_add(env->vcamera, vforward);
	if (keys[SDL_SCANCODE_S] == 1)
			env->vcamera = vec_sub(env->vcamera, vforward);
	if (keys[SDL_SCANCODE_A] == 1)
			env->vcamera = vec_add(env->vcamera, vright);
	if (keys[SDL_SCANCODE_D] == 1)
			env->vcamera = vec_sub(env->vcamera, vright);
	move->dy = 0.02f;
}

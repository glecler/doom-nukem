/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:30:37 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		ft_putstr("SDL_Init error\n");
		exit(0);
	}
	if (!(sdl->window = SDL_CreateWindow("DOOM_TEST",
					SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SIZE_X, SIZE_Y, 0)))
	{
		ft_putstr("SDL_CreateWindow error\n");
		exit(0);
	}
	if (!(sdl->render = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_PRESENTVSYNC)))
	{
		ft_putstr("SDL_CreateRenderer error\n");
		exit(0);
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void init_vec(t_vec3d *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 1.0f;
}

void 	clean_quit(t_sdl *sdl, t_env *env)
{
	int i;
	int n;

	n = -1;
	while (++n < env->nb_tex)
	{
		i = -1;
		while (++i < env->tex[n].y)
		{
			free(env->tex[n].pixels[i]);
			free(env->tex[n].alphas[i]);
		}
		free(env->tex[n].name);
		free(env->tex[n].pixels);
		free(env->tex[n].alphas);
	}
	free(env->tex);
	free(env->tri);
	free(env->obb);
	SDL_DestroyRenderer(sdl->render);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	exit(0);
}

void	mouse_cam(t_env *env, t_sdl *sdl)
{
	float 		rad;
	int 	x;
	int 	y;
	int 	reset;

	SDL_GetRelativeMouseState(&x, &y);
	reset = (int)(360.0f / MSPEED);
	rad = M_PI / 180.0f;
	sdl->x += x;
	if (sdl->x > reset)
		sdl->x -= reset;
	else if (sdl->x < - reset)
		sdl->x += reset;
	env->fyaw = sdl->x * MSPEED * rad;
	if ((sdl->y + y) * MSPEED * rad < 90.0f * rad && (sdl->y + y) * MSPEED * rad > -90.0f * rad)
	{
		sdl->y += y;
		env->fpitch = sdl->y * MSPEED * rad;
	}
}

void 	save_tour(t_env *env)
{
	int i, j, k;
	int tour;

	i = -1;
	tour = 0;
	while (++i <= env->nb_obb)
	{
		if (env->obb[i].id == 4)
			tour++;
	}
	if (!(env->tour = malloc(sizeof(t_triangle  *) * tour)))
			exit(0);
	i = -1;
	while (++i < tour)
	{
		if (!(env->tour[i] = malloc(sizeof(t_triangle) * 12)))
				exit(0);
	}
	i = -1;
	k = 0;
	while (++i <= env->nb_obb)
	{
		if (env->obb[i].id == 4)
		{
			j = env->obb[i].first - 1;
			while (++j <= env->obb[i].last)
				env->tour[k][j - env->obb[i].first] = env->tri[j];
			k++;
		}
	}
}

void 	face_tourelle(t_env *env, t_obb obb, t_triangle  *tour)
{
	float	x, z;
	float angle;
	int i;
	int d;
	t_mat4x4 mat;

	x = env->vcamera.x - obb.center.x;
	z = env->vcamera.z - obb.center.z;
	angle = atan2f(z, x) * 180 / M_PI;
	if (angle < 0)
		angle += 360;
	angle *= M_PI / 180.0f;
	mat = init_matroty(angle);
	i = -1;
	while (++i < obb.last - obb.first)
	{
		d = -1;
		while (++d < 3)
		{
			env->tri[i + obb.first].p[d] = mat_mulvec(mat, vec_sub(tour[i].p[d], obb.center));
			env->tri[i + obb.first].p[d] = vec_add(env->tri[i + obb.first].p[d], obb.center);
		}
	}
}

void 	move_tourelle(t_env *env)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i <= env->nb_obb)
	{
		if (env->obb[i].id == 4)
		{
			face_tourelle(env, env->obb[i], env->tour[j]);
			j++;
		}
		if (env->obb[i].id == -3)
			j++;
		i++;
	}
}

int 	hit_player(t_vec3d tir, t_obb *obb, int borne, t_env *env)
{
	int i;
	t_vec3d max;
	t_vec3d min;
	t_vec3d pmax;
	t_vec3d pmin;
	float		*data_vec;

	if (!(data_vec = malloc(sizeof(float) * 6)))
		exit (0);
	i = 0;
	init_vec(&pmax, env->vcamera.x + 1, env->vcamera.y + 1, env->vcamera.z + 1);
	init_vec(&pmin, env->vcamera.x - 1, env->vcamera.y - 1, env->vcamera.z - 1);
	while (i <= borne)
	{
		if (obb[i].id != 4)
		{
			obb[i].halfsize.x -= 3;
			obb[i].halfsize.y -= 3;
			obb[i].halfsize.z -= 3;
			init_col(data_vec, obb[i].center, obb[i].halfsize);
			obb[i].halfsize.x += 3;
			obb[i].halfsize.y += 3;
			obb[i].halfsize.z += 3;
			init_vec(&max, data_vec[0], data_vec[1], data_vec[2]);
			init_vec(&min, data_vec[3], data_vec[4], data_vec[5]);
			if (tir.x >= pmin.x && tir.y >= pmin.y && tir.z >= pmin.z && \
				tir.x <= pmax.x && tir.y <= pmax.y && tir.z <= pmax.z)
			{
				free(data_vec);
				return(2);
			}
			else if (tir.x >= min.x && tir.y >= min.y && tir.z >= min.z && \
				tir.x <= max.x && tir.y <= max.y && tir.z <= max.z)
			{
				free(data_vec);
				return(1);
			}
		}
		i++;
	}
	free(data_vec);
	return (0);
}

void 	piou_tourelle(t_env *env, t_obb obb)
{
	float	x, z;
	float angle;
	t_vec3d tir;
	t_vec3d dtir;

	x = env->vcamera.x - obb.center.x;
	z = env->vcamera.z - obb.center.z;
	angle = atan2f(z, x) * 180 / M_PI;
	if (angle < 0)
		angle += 360;
	angle *= M_PI / 180.0f;
	init_vec(&tir, cos(angle), 0.0f, sin(angle));
	dtir = vec_add(tir, obb.center);
	while (hit_player(dtir, env->obb, env->nb_obb, env) == 0)
		dtir = vec_add(dtir, tir);
	if (hit_player(dtir, env->obb, env->nb_obb, env) == 2)
	{
		env->hp -= 20.0f;
		if (env->hp == 0)
		{
			env->vcamera = env->spawn;
			env->dy = 1;
			env->hp = 100;
			env->nrj = 100;
		}
	}
}

void 	shoot_tourelle(t_env *env)
{
	int i;

	i = 0;
	while (i <= env->nb_obb)
	{
		if (env->obb[i].id == 4)
			piou_tourelle(env, env->obb[i]);
		i++;
	}
}

void anim_port(t_env *env, unsigned int	tick)
{
	unsigned int	tick1;

	tick1 = SDL_GetTicks();
	if ((tick1 % 2) == 0)
		texture_portal(env->obb, env);
	else
		texture_portal2(env->obb, env);
	if (tick1 - tick > 1500)
	{
		texture_portal(env->obb, env);
		env->end++;
	}
}

// fonction pour clean event
void	get_event(t_sdl *sdl, t_env *env)
{
 	const Uint8 	*keys;
	t_move				move;
	unsigned int	tick[6];

	init_move(&move);
	tick[0] = 0;
	tick[1] = 0;
	tick[2] = 0;
	tick[3] = SDL_GetTicks();
	tick[4] = 0;
	tick[5] = SDL_GetTicks();
	while (SDL_PollEvent(&sdl->event) == 1 || SDL_PollEvent(&sdl->event) == 0)
	{
		keys = SDL_GetKeyboardState(NULL);
		if ((keys[SDL_SCANCODE_ESCAPE] == 1 || (sdl->event.type == SDL_QUIT)))
			clean_quit(sdl, env);
		if (env->fin == 0)
		{
			if (keys[SDL_SCANCODE_E] == 1 || SDL_GetTicks() - tick[3] > 17000)
				env->intro = 1;
			if ((keys[SDL_SCANCODE_P] == 1 && SDL_GetTicks() - tick[0] > 2000) || env->vcamera.y < -1500.0f )
			{
				env->vcamera = env->spawn;
				env->hp = 20;
				sdl->x = 0;
				sdl->y = 0;
				move.dy = 0.02f;
				tick[0] = SDL_GetTicks();
			}
			if (keys[SDL_SCANCODE_K] == 1 && SDL_GetTicks() - tick[1] > 250)
			{
				move.fly *= -1;
				tick[1] = SDL_GetTicks();
			}
			if (keys[SDL_SCANCODE_F] == 1 && env->r_hp == 1 && env->hp != 100)
			{
				env->r_hp = 0;
				env->hp	= 100;
			}
			if ((env->nrj == 0  && SDL_GetTicks() - tick[2] > 1500))
			{
				env->nrj = 100;
				tick[2] = SDL_GetTicks();
			}
			get_move(&move, keys);
			mouse_cam(env, sdl);
			physic(env, &move, keys);
			if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				if (env->nrj > 0  && SDL_GetTicks() - tick[2] > 400)
				{
					env->nrj -= 20;
					env->shoot = 1;
					shoot(env);
					tick[2] = SDL_GetTicks();
					if (env->end == 7 && env->end++)
						tick[4] = tick[2];
				}
			}
			if (env->end == 8)
				anim_port(env, tick[4]);
			if (SDL_GetTicks() - tick[2] > 200)
				env->shoot = 0;
			move_tourelle(env);
			if (SDL_GetTicks() - tick[5] > 3000)
			{
				shoot_tourelle(env);
				tick[5] = SDL_GetTicks();
			}
		}
		display(sdl, env);
 	}
}

void main_init(t_sdl *sdl, t_env *env)
{
	ft_init_sdl(sdl);
	init_vec(&env->vlookdir, 0.0f, 0.0f, 1.0f);
	init_vec(&env->vcamera, 0.0f, 0.0f, 0.0f);
	init_vec(&env->spawn, 0.0f, 0.0f, 0.0f);
	env->tri = NULL;
	env->tour = NULL;
	env->tex = NULL;
	env->fyaw = 0.0f;
	env->fpitch = 0.0f;
	env->crunch = 0.0f;
	env->hp = 100;
	env->r_hp = 0;
	env->nrj = 0;
	env->shoot = 0;
	env->dy = 0;
	env->intro = 0;
	env->end = 0;
	env->fin = 0;
	env->matproj = mat_makeproj(90.0f, (float)SIZE_Y / (float)SIZE_X, 0.1f, 1000.0f);
	sdl->x = 0;
	sdl->y = 0;
}

int	main(int ac, char **av)
{
	t_sdl		sdl;
	t_env		env;
	t_vec3d		*list;
	t_vec2d		*uv;

	(void)ac;
	main_init(&sdl, &env);
	list = NULL;
	uv = NULL;
	env = parse(av[1], env, list, uv);
	env.tex = xpm_parser(env.tex, env.nb_tex);
	save_tour(&env);
	display(&sdl, &env);
	get_event(&sdl, &env);
	return (0);
}

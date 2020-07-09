/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:45:03 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		skip(char *str, int i)
{
	while (str[i] && str[i] > 32)
		i++;
	while (str[i] && str[i] <= 32)
		i++;
	return (i);
}

t_vec3d		p_vec(char *str, t_vec3d vec)
{
	int	i;

	i = 0;
	i = skip(str, i);
	vec.x = ft_atof(str + i);
	i = skip(str, i);
	vec.y = ft_atof(str + i);
	i = skip(str, i);
	vec.z = ft_atof(str + i);
	vec.w = 1.0f;
	return (vec);
}

t_triangle		p_tri(char *str, t_triangle tri, t_vec3d *list, t_vec2d *uv)
{
	int	i;

	i = 0;
	i = skip(str, i);
	tri.p[0] = list[ft_atoi(str + i) - 1];
	while(str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '/')
			tri.t[0] = uv[ft_atoi(str + i + 1) - 1];
	i = skip(str, i);
	tri.p[1] = list[ft_atoi(str + i) - 1];
	while(str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '/')
			tri.t[1] = uv[ft_atoi(str + i + 1) - 1];
	i = skip(str, i);
	tri.p[2] = list[ft_atoi(str + i) - 1];
	while(str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '/')
			tri.t[2] = uv[ft_atoi(str + i  + 1) - 1];
	return (tri);
}

t_env	parse(char *file_name, t_env env, t_vec3d *list, t_vec2d *uv)
{
	int		fd;
	char	*buff;
	int		ret;
	int		v[2];
	int 	m[3];
	int 	o[2];

	v[0] = 0;
	v[1] = 0;
	env.nb_obb = -1;
	env.nb_tex = 0;
	env.nb_tri = 0;
	m[0] = 1;
	m[1] = 1;
	m[2] = 1;
	o[0] = 1;
	if ((fd = open(file_name, O_RDONLY)) < 0)
		exit(0);
	if (!(env.tex = malloc(sizeof(t_texture) * (1024))))
			exit(0);
	env.obb = NULL;
	while ((ret = get_next_line(fd, &buff)) == 1)
	{
		if (buff[0] == 'v' && buff[1] == 32)
		{
			if (v[0] % 4096 == 0)
			{
				list = vec_add_size(list, m[0]);
				m[0]++;
			}
			list[v[0]] = p_vec(buff, list[v[0]]);
			v[0]++;
		}
		else if (buff[0] == 's' && buff[1] == 'p' && buff[2] == 'a' && \
			buff[3] == 'w' && buff[4] == 'n')
			get_spawn(&env, buff);
		else if (buff[0] == 'v' && buff[1] == 't' && buff[2] == 32)
		{
			if (v[1] % 4096 == 0)
			{
				uv = vec2_add_size(uv, m[2]);
				m[2]++;
			}
			uv[v[1]] = p_vec2(buff, uv[v[1]]);
			v[1]++;
		}
		else if (buff[0] == 'u' && buff[1] == 's' && buff[2] == 'e' && \
			buff[3] == 'm' && buff[4] == 't' && buff[5] == 'l' && buff[6] == 32)
		{
			env.tex[env.nb_tex] = get_tex_name(buff, env.tex[env.nb_tex]);
			env.nb_tex++;
		}
		else if (buff[0] == 'f' && buff[1] == 32)
		{
			if (env.nb_tri % 4096 == 0)
			{
				env.tri = tri_add_size(env.tri, m[1]);
				m[1]++;
			}
			env.tri[env.nb_tri] = p_tri(buff, env.tri[env.nb_tri], list, uv);
			env.tri[env.nb_tri].index = env.nb_tex - 1; //Index Text / Tri
			env.nb_tri++;
		}
		else if (buff[0] == 'o' && buff[1] == 32)
		{
			if (env.nb_obb + 1 % 4096 == 0)
			{
				env.obb = obb_add_size(env.obb, o[0]);
				o[0]++;
			}
			env.obb[env.nb_obb + 1].id = 0;
			if (env.nb_obb != -1)
				env.obb[env.nb_obb] = p_obb(env.obb[env.nb_obb], env.tri + o[1], env.nb_tri - 1 - o[1], o[1]);
			o[1] = env.nb_tri;
			env.nb_obb++;
		}
		else if (buff[0] == 'i' && buff[1] == 'd')
			env.obb[env.nb_obb].id = ft_atoi(buff + 3);
		free(buff);
	}
	env.obb[env.nb_obb] = p_obb(env.obb[env.nb_obb], env.tri + o[1], env.nb_tri - 1 - o[1], o[1]);
	close(fd);
	free(uv);
	free(list);
	return (env);
}

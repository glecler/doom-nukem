/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_thread_tools_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:33:13 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_triangle *tri_memcpy_n(t_triangle *dest, t_triangle *src, int start, int end)
{
 	int i;

	i = 0;
	while (start + i < end)
	{
		dest[i] = src[start + i];
		i++;
	}
	return (dest);
}

t_triangle *tri_mem_join(t_triangle *dest, t_triangle *src, int start, int end)
{
	int i;

	i = 0;
	while (i < end)
	{
		dest[start + i] = src[i];
		i++;
	}
  free(src);
	return (dest);
}

// struct var + norme
t_triangle	*after_clip(t_triangle *tri_proj, int start, int *end)
{
	t_triangle *cpy_tri;
	t_triangle *tmp_tri;
	t_triangle	clipped[2];
	t_vec3d plane[7];
	int nclipped;
	int p;
	int k;
	int i;

	init_plane(plane);
	nclipped = 0;
	p = 0;
	if (!(tmp_tri = malloc(sizeof(t_triangle) * (*end - start))))
		exit (0);
	tmp_tri = tri_memcpy_n(tmp_tri, tri_proj, start, *end);
	*end -= start;
	while (p < 4)
	{
		i = 0;
		k = 0;
		if (!(cpy_tri = malloc(sizeof(t_triangle) * (*end * 2))))
			exit (0);
	 	while (i < *end)
		{
			nclipped = clip_all_plane(p, plane, tmp_tri[i], clipped);
			new_clip_tri(i, nclipped, &k, clipped, cpy_tri);
			i++;
		}
		*end += k;
		tmp_tri = alloc_tri(tmp_tri, *end, cpy_tri);
    free(cpy_tri);
		p++;
	}
	return (tmp_tri);
}

void	clip_thread(t_draw_worker *arg)
{
	arg->tmp_tri = after_clip(arg->tri_proj, arg->start, &arg->end);
}

// struct var + norme
t_triangle *do_thread(t_triangle *tri_proj, int *d, int nb_thread)
{
	t_triangle		*n_tri;
	pthread_t		thread[nb_thread];
	t_draw_worker	arg[nb_thread];
	int 			ret;
	int				i;

	i = 0;
	while (i < nb_thread)
	{
		arg[i] = (t_draw_worker)
		{
			.tri_proj = tri_proj,
		  .tmp_tri = NULL,
		  .start = i * (*d) / nb_thread,
		  .end = (i + 1) * (*d) / nb_thread
		};
		if((ret = pthread_create(&thread[i], NULL, (void *)clip_thread, arg + i)) == -1)
			exit (0);
		i++;
	}
	while (i--)
		pthread_join(thread[i], NULL);
	i += 1;
	*d = 0;
	while (i < nb_thread)
	{
		*d += arg[i].end;
		i++;
	}
	i = 0;
	if (!(n_tri = malloc(sizeof(t_triangle) * (*d))))
		exit (0);
    *d = 0;
	while (i < nb_thread)
	{
		if (i == 0)
			n_tri = tri_mem_join(n_tri, arg[i].tmp_tri, 0, arg[i].end);
		else
			n_tri = tri_mem_join(n_tri, arg[i].tmp_tri, *d, arg[i].end);
    *d += arg[i].end;
		i++;
	}
	return (n_tri);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:33:13 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

// struct var
void  display_surface(t_depth *depth, t_sdl *sdl)
{
  int r, g, b;
  int x, y;

  y = 0;
  while (y < SIZE_Y)
  {
    x = 0;
    while (x < SIZE_X)
    {
      if (depth[y * SIZE_X + x].w != 0.0f)
      {
        r = depth[y * SIZE_X + x].color / (256 * 256);
        g = depth[y * SIZE_X + x].color / 256 % 256;
        b = depth[y * SIZE_X + x].color % 256;
        ((uint32_t*)sdl->surface->pixels)[x + y * SIZE_X] = SDL_MapRGBA(sdl->surface->format, r, g, b, 255);
      }
      else
        ((uint32_t*)sdl->surface->pixels)[x + y * SIZE_X] = SDL_MapRGBA(sdl->surface->format, 0, 0, 0, 0);
      x++;
    }
    y++;
  }
  sdl->texture = SDL_CreateTextureFromSurface(sdl->render, sdl->surface);
  SDL_FreeSurface(sdl->surface);
  SDL_RenderCopy(sdl->render, sdl->texture, NULL, NULL);
  SDL_DestroyTexture(sdl->texture);
}

// struct var
void    tri_to_pixel(t_sdl *sdl, t_triangle *tri_proj, int d, t_env *env)
{
  t_triangle  *n_tri;
  int          nb_thread;
  t_depth     *depth;
  int				   i;
  uint32_t     rmask, gmask, bmask, amask;

  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
  nb_thread = (d < NB_THREAD)? d : NB_THREAD;
  n_tri = do_thread(tri_proj, &d, nb_thread);
  if (!(depth = malloc(sizeof(t_depth) * (SIZE_X * SIZE_Y))))
    exit (0);
  i = 0;
  while (i < SIZE_X * SIZE_Y)
  {
    depth[i].w = 0.0f;
    depth[i].color = 0;
    i++;
  }
  i = 0;
  while(i < d)
  {
    fill_texture(n_tri[i], env->tex[n_tri[i].index], depth);
    i++;
  }
  sdl->surface = SDL_CreateRGBSurface(0, 800, 600, 32, rmask, gmask, bmask, amask);
  display_surface(depth, sdl);
  free(depth);
  free(n_tri);
}

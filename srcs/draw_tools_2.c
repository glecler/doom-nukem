/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/10 16:55:46 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void  draw_weapon(t_sdl *sdl, t_env *env)
{
  uint32_t     rmask, gmask, bmask, amask;
  SDL_Surface *weapon;
  SDL_Surface *laser;

  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
  weapon = SDL_CreateRGBSurface(0, 200, 166, 32, rmask, gmask, bmask, amask);
  fill_surface(weapon, env->tex[env->nb_tex - 10], 200, 166);
  surf_render(sdl, weapon, 468, 435, 200, 166);
  if (env->shoot == 1)
  {
    laser = SDL_CreateRGBSurface(0, 98, 169, 32, rmask, gmask, bmask, amask);
    fill_surface(laser, env->tex[env->nb_tex - 9], 98, 169);
    surf_render(sdl, laser, 400, 290, 98, 169);
  }
}

void  draw_hud(t_sdl *sdl, t_env *env)
{
  uint32_t     rmask, gmask, bmask, amask;
  SDL_Surface *jauge_hp;
  SDL_Surface *jauge_nrj;
  SDL_Surface *jauge;

  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
  jauge_hp = SDL_CreateRGBSurface(0, 156, 26, 32, rmask, gmask, bmask, amask);
  jauge_nrj = SDL_CreateRGBSurface(0, 156, 26, 32, rmask, gmask, bmask, amask);
  jauge = SDL_CreateRGBSurface(0, 108, 54, 32, rmask, gmask, bmask, amask);
  fill_surface(jauge_hp, env->tex[env->nb_tex - 3 - (env->hp / 20)], 156, 26);
  fill_surface(jauge_nrj, env->tex[env->nb_tex - 3 - (env->nrj / 20)], 156, 26);
  fill_surface(jauge, env->tex[env->nb_tex - 2], 108, 54);
  surf_render(sdl, jauge_nrj, 108, 525, 156, 26);
  surf_render(sdl, jauge_hp, 108, 556, 156, 26);
  surf_render(sdl, jauge, 0, 525, 108, 54);
}

void  draw_intro(t_sdl *sdl, t_env *env)
{
  uint32_t     rmask, gmask, bmask, amask;
  SDL_Surface *border;

  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
  border = SDL_CreateRGBSurface(0, 800, 150, 32, rmask, gmask, bmask, amask);
  fill_surface(border, env->tex[env->nb_tex - 11], 800, 150);
  surf_render(sdl, border, 0, 450, 800, 150);
}

void  draw_r_hp(t_sdl *sdl, t_env *env, int i)
{
  uint32_t     rmask, gmask, bmask, amask;
  SDL_Surface *orbe;

  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
  orbe = SDL_CreateRGBSurface(0, 21, 21, 32, rmask, gmask, bmask, amask);
  fill_surface(orbe, env->tex[env->nb_tex - 16 - i], 21, 21);
  surf_render(sdl, orbe, 270, 560, 21, 21);
}

void  draw_fin(t_sdl *sdl, t_env *env)
{
  uint32_t     rmask, gmask, bmask, amask;
  SDL_Surface *border;

  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
  border = SDL_CreateRGBSurface(0, 800, 600, 32, rmask, gmask, bmask, amask);
  fill_surface(border, env->tex[env->nb_tex - 18], 800, 600);
  surf_render(sdl, border, 0, 0, 800, 600);
}
//struct pour rgb
//struct pour token affichage
void  draw_stuff(t_sdl *sdl, t_env *env)
{
  if (env->intro == 0)
    draw_intro(sdl, env);
  else
  {
    if (env->r_hp == 0)
      draw_r_hp(sdl, env, 0);
    else
      draw_r_hp(sdl, env, 1);
    draw_weapon(sdl, env);
    draw_hud(sdl, env);
  }
  draw_crosshair(sdl);
  if (env->fin == 1)
    draw_fin(sdl, env);
}

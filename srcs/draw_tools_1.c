/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/02/10 16:55:46 by mamisdra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void  fill_surface(SDL_Surface *surf, t_texture tex, int x, int y)
{
  int r, g, b, a;
  int i, j;

  i = 0;
  while (i < y)
  {
    j = 0;
    while (j < x)
    {
      r = tex.pixels[i][j] / (256 * 256);
      g = tex.pixels[i][j] / 256 % 256;
      b = tex.pixels[i][j] % 256;
      a = tex.alphas[i][j];
      ((uint32_t*)surf->pixels)[j + i * x] = SDL_MapRGBA(surf->format, r, g, b, a);
      j++;
    }
    i++;
  }
}

void  surf_render(t_sdl *sdl, SDL_Surface *surface, int x, int y, int i, int j)
{
  SDL_Rect rect;

  rect.x = x;
  rect.y = y;
  rect.w = i;
  rect.h = j;
  sdl->texture = SDL_CreateTextureFromSurface(sdl->render, surface);
  SDL_FreeSurface(surface);
  SDL_RenderCopy(sdl->render, sdl->texture, NULL, &rect);
  SDL_DestroyTexture(sdl->texture);
}

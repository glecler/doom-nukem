/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_xmp_parser_tool_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/08 18:58:55 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int  hex_to_dec(char *hex)
{
  int dec;
  int len;
  int val;
  int i;

  i = 0;
  len = ft_strlen(hex) - 1;
  dec = 0;
  while (hex[i] != '\0')
  {
    if(hex[i] >= '0' && hex[i] <= '9')
      val = hex[i] - 48;
    else if(hex[i] >= 'a' && hex[i] <= 'f')
      val = hex[i] - 97 + 10;
    else if(hex[i] >= 'A' && hex[i] <= 'F')
      val = hex[i] - 65 + 10;
    dec += val * pow(16, len);
    len--;
    i++;
  }
  return (dec);
}

void xpm_malloc(t_texture *tex, t_tex_data *data)
{
  int i;

  i = -1;
  if(!(data->dico = malloc(sizeof(char *) * data->nb_color)))
    exit(0);
  while (++i < data->nb_color)
  {
    if(!(data->dico[i] = malloc(sizeof(char) * data->cpp + 1)))
      exit(0);
  }
  if(!(data->trad = malloc(sizeof(int) * data->nb_color)))
    exit(0);
  if(!(data->alpha = malloc(sizeof(int) * data->nb_color)))
    exit(0);
  if(!(tex->pixels = malloc(sizeof(int *) * tex->y)))
    exit(0);
  if(!(tex->alphas = malloc(sizeof(int *) * tex->y)))
    exit(0);
  i = -1;
  while (++i < tex->y)
  {
    if(!(tex->pixels[i] = malloc(sizeof(int) * tex->x)))
      exit(0);
    if(!(tex->alphas[i] = malloc(sizeof(int) * tex->x)))
      exit(0);
  }
}

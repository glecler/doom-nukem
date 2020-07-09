/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_xmp_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/08 18:58:55 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void      xpm_header(t_texture *tex, t_tex_data *data, char *buff)
{
  int i;
  i = 1;
  tex->x = ft_atoi(buff + i);
  i = skip(buff, i);
  tex->y = ft_atoi(buff + i);
  i = skip(buff, i);
  data->nb_color = ft_atoi(buff + i);
  i = skip(buff, i);
  data->cpp = ft_atoi(buff + i);
  xpm_malloc(tex, data);
}

void      xpm_translator(t_tex_data *data, char *buff)
{
  int i;
  int n;
  char hex[7];

  i = 1;
  n = -1;
  while (++n < data->cpp)
  {
    data->dico[data->index][n] = buff[i];
    i++;
  }
  data->dico[data->index][n] = '\0';
  i += 3;

  if (buff[i] == '#')
  {
    i++;
    data->trad[data->index] = hex_to_dec(ft_strncpy(hex, buff + i, 6));
    data->alpha[data->index] = 255;
  }
  else if (ft_strncmp("None", buff + i, 4) == 0)
  {
    data->trad[data->index] = 0;
    data->alpha[data->index] = 0;
  }
}

void      xpm_reader(t_texture *tex, t_tex_data *data, char *buff)
{
  char  *cp;
  int   i;
  int   n;
  int   k;

  i = 1;
  k = -1;
  while(++k < tex->x)
  {
    n = 0;
    if(!(cp = malloc(sizeof(char) * data->cpp + 1)))
      exit(0);
    cp = ft_strncpy(cp, buff + i, data->cpp);
    while(ft_strcmp(cp, data->dico[n]) != 0)
      n++;
    tex->pixels[data->index][k] = data->trad[n];
    tex->alphas[data->index][k] = data->alpha[n];
    i += data->cpp;
    free(cp);
  }
}

//struct reading
void      read_tex(t_texture *tex)
{
  int fd;
  int ret;
  char *buff;
  int token;
  t_tex_data data;

  token = 0;
  data.index = 0;
  tex->name = ft_strcatr(tex->name, "assets/");
  if ((fd = open(tex->name, O_RDONLY)) < 0)
		exit(0);
  while ((ret = get_next_line(fd, &buff)) == 1)
  {
    if (ft_strcmp(buff, "/* pixels */\0") == 0)
    {
      token = 2;
      data.index = 0;
    }
    else if (buff[0] == '"')
    {
      if (token == 0)
      {
        xpm_header(tex, &data, buff);
        token = 1;
      }
      else if (token == 1)
      {
        xpm_translator(&data, buff);
        data.index++;
      }
      else
      {
        xpm_reader(tex, &data, buff);
        data.index++;
      }
    }
    free(buff);
  }
  free(data.trad);
  ret = -1;
  while (++ret < data.nb_color)
    free(data.dico[ret]);
  free(data.dico);
  free(data.alpha);
}

t_texture *xpm_parser(t_texture *tex, int nb_tex)
{
  int   i;

  i = 0;
  while (i < nb_tex)
  {
    read_tex(&tex[i]);
    i++;
  }
  return(tex);
}

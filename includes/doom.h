/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:15:28 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "../libft/includes/libft.h"
//# include "../libvector/includes/libvector.h"
# include "SDL2/SDL.h"
# include "math.h"
# include <pthread.h>
# define SIZE_X 800
# define SIZE_Y 600
# define MSPEED 0.12f
# define SPEED 0.75f
# define RUNSPEED 4.0f
# define NB_THREAD 8

typedef struct  s_mat4x4
{
  float m[4][4];
}               t_mat4x4;

typedef struct	s_bres
{
    int x0;
    int y0;
    int x1;
    int y1;
    int dx;
    int sx;
    int dy;
    int sy;
    int err;
    int e2;
}				        t_bres;

typedef struct	s_tex_var
{
  int r;
  int g;
  int b;
  int dy1;
  int dx1;
  float dv1;
  float du1;
  float dw1;
  int dy2;
  int dx2;
  float dv2;
  float du2;
  float dw2;
  float tex_u;
  float tex_v;
  float tex_w;
  float dax_step;
  float dbx_step;
  float du1_step;
  float dv1_step;
	float	du2_step;
  float dv2_step;
	float	dw1_step;
  float dw2_step;
  int ax;
  int bx;
  float tex_su;
  float tex_sv;
  float tex_sw;
  float tex_eu;
  float tex_ev;
  float tex_ew;
  float tstep;
  float t;
  int   tex_x;
  int   tex_y;
}               t_tex_var;

typedef struct  s_sdl
{
    SDL_Window		*window;
    SDL_Renderer	*render;
    SDL_Surface   *surface;
    SDL_Texture   *texture;
    SDL_Event       event;
    int             x;
    int             y;

}               t_sdl;

typedef struct  s_texture
{
  char  *name;
  int  **pixels;
  int  **alphas;
  int   x;
  int   y;
}               t_texture;

typedef struct  s_tex_data
{
  int   nb_color;
  int   cpp; //char per pixels
  char  **dico;
  int   *trad;
  int   *alpha;
  int   index;
}               t_tex_data;

typedef struct  s_vec3d
{
  float x;
  float y;
  float z;
  float w;
}               t_vec3d;

typedef struct  s_vec2d
{
  float u;
  float v;
  float w;
}               t_vec2d;

typedef struct  s_triangle
{
    t_vec3d p[3];
    t_vec2d t[3];
    float   dp;
    int     index;
}               t_triangle;

typedef struct  s_obb
{
  int       id;
  int       first;
  int       last;
  t_vec3d   center;
  t_vec3d   halfsize;
}               t_obb;

typedef struct  s_env
{
  t_triangle  *tri;
  t_triangle  **tour;
  t_vec3d		  vlookdir;
  t_vec3d		  vlookright;
  t_vec3d		  vcamera;
  t_vec3d		  spawn;
  t_mat4x4    matproj;
  int         nb_tri;
  int         nb_tex;
  int         nb_obb;
  int         hp;
  int         r_hp;
  int         nrj;
  int         shoot;
  int         dy;
  int         intro;
  int         end;
  int         fin;
  float 	   	fyaw;
  float       fpitch;
  float       crunch;
  t_texture   *tex;
  t_obb       *obb;
}               t_env;

 typedef struct   s_world
 {
   t_mat4x4    matrotz;
   t_mat4x4    matrotx;
   t_mat4x4    mattrans;
   t_mat4x4 	 matworld;
   t_mat4x4		 matcam;
   t_mat4x4		 matview;
   t_vec3d		 vcam_ray;
   t_vec3d		 vup;
   t_vec3d		 vtarget;
   t_vec3d		 vright;
   t_vec3d 		 normal;
   int 				 i;
 }                t_world;

 typedef struct   s_clipz
 {
   int        nclipped;
   int        n;
   t_triangle clipped[2];
   t_vec3d    plane_p;
   t_vec3d    plane_n;
   float      color;
 }                t_clipz;

typedef struct   s_depth
{
  int   color;
  float w;
}                t_depth;

typedef struct		s_draw_worker
{
  t_triangle  *tri_proj;
  t_triangle  *tmp_tri;
  int         start;
  int         end;
}                 t_draw_worker;

typedef struct		s_depth_worker
{
  t_triangle  *tri;
  t_texture   *tex;
  t_depth     *depth;
  int         start;
  int         end;
}                 t_depth_worker;

typedef struct		s_move
{
  float   velocity;
  float   speed;
  float   gravity;
  float   dy;
  int     jump;
  int     crouch;
  int     fly;
  int     flag;
}                 t_move;

/* Sort Fonction by file */
/* main.c */
void    init_vec(t_vec3d *v, float x, float y, float z);
/* world_gen */
void    display(t_sdl *sdl, t_env *env);
/* world_gen_tools_1 */
float     	shade_light(t_vec3d normal, t_vec3d vcamera);
t_triangle	scale_screen(t_triangle tri);
void        draw_crosshair(t_sdl *sdl);
t_triangle  trans_mat(t_triangle tri_trans, t_world *world, t_env *env);
t_triangle	world_to_view(t_triangle t_trs, t_triangle t_vw, t_world world);
/* world_gen_tools_2 */
t_triangle  projection(t_triangle tri_proj, t_clipz clipz, t_env *env);
/* fill_triangle */
void 	fill_triangle(t_triangle tri, t_sdl *sdl);
/* shoot */
void texture_portal2(t_obb *obb, t_env *env);
void texture_portal(t_obb *obb, t_env *env);
void 	shoot(t_env *env);
/* movement */
void 	init_move(t_move *move);
void 	get_move(t_move *move, const Uint8 *keys);
void   physic(t_env *env, t_move *move, const Uint8 *keys);
int    collide_ground(t_obb *obb, t_vec3d cam, int nb_obb, float speed);
/* movement_tools_1 */
void 	  init_col(float *data_vec, t_vec3d cent, t_vec3d half);
void    crouching(t_env *env, t_move *move, const Uint8 *keys);
void    vanish_item(t_env *env, t_obb obb);
int     collide(t_env *env, t_vec3d cam, int flag, float speed);
void 	  fly(t_env *env, t_move *move, const Uint8 *keys);
/* obj_parser */
t_env	    parse(char *file_name, t_env env, t_vec3d *list, t_vec2d *uv);
int       skip(char *str, int i);
/* obj_parser_tools */
t_vec3d     *vec_add_size(t_vec3d *data, int size);
t_triangle  *tri_add_size(t_triangle *data, int size);
t_triangle *tri_memcpy(t_triangle *dest, t_triangle *src, size_t n);
/* obj_parser_tools_2 */
t_vec2d     *vec2_add_size(t_vec2d *data, int size);
t_vec2d     p_vec2(char *str, t_vec2d vec);
t_texture	  get_tex_name(char *buff, t_texture tex);
/* obj_parser_tools_3 */
void 	get_spawn(t_env *env, char *str);
t_obb *obb_add_size(t_obb *data, int size);
t_obb p_obb(t_obb obb, t_triangle *tri, int nb, int first);
/* draw_tool */
void    init_bres(t_vec3d v0, t_vec3d v1, t_bres *bres);
void    drawline(t_vec3d v0, t_vec3d v1, t_sdl *sdl);
/* draw_tools_1 */
void  surf_render(t_sdl *sdl, SDL_Surface *surface, int x, int y, int i, int j);
void  fill_surface(SDL_Surface *surf, t_texture tex, int x, int y);
/* draw_tools_2 */
void  draw_hud(t_sdl *sdl, t_env *env);
void  draw_weapon(t_sdl *sdl, t_env *env);
void  draw_intro(t_sdl *sdl, t_env *env);
void  draw_stuff(t_sdl *sdl, t_env *env);
/* algo_tools_tool */
void        swap_v(t_vec3d *v1, t_vec3d *v2);
void        swap_v2(t_vec2d *v1, t_vec2d *v2);
void		    swap_f(float *v1, float *v2);
void		    swap_t(t_triangle *t1, t_triangle *t2);
void		    swap_i(int *v1, int *v2);
/* display_tools_1 */
void	tri_to_pixel(t_sdl *sdl, t_triangle *tri_proj, int d, t_env *env);
/* display_tools_2 */
void draw_tri(t_sdl *sdl, t_triangle t);
void init_plane(t_vec3d *plane);
int	clip_all_plane(int p, t_vec3d *plane, t_triangle tmp_tri, t_triangle *clipped);
void new_clip_tri(int i, int nclipped, int *k, t_triangle *clipped, t_triangle *cpy_tri);
t_triangle *alloc_tri(t_triangle *tmp_tri, int d, t_triangle *cpy_tri);
/* display_thread_tools_2 */
t_triangle *do_thread(t_triangle *tri_proj, int *d, int nb_thread);
/* vector_tools_1 */
t_vec3d vec_add(t_vec3d v1, t_vec3d v2);
t_vec3d vec_sub(t_vec3d v1, t_vec3d v2);
t_vec3d vec_mul(t_vec3d v1, float k);
t_vec3d vec_div(t_vec3d v1, float k);
/* vector_tools_2 */
float   dot_product(t_vec3d v1, t_vec3d v2);
float   vec_len(t_vec3d v1);
t_vec3d vec_normalise(t_vec3d v1);
t_vec3d cross_product(t_vec3d v1, t_vec3d v2);
t_vec3d	calc_normal(t_vec3d normal, t_triangle tri_trans);
/* matrice_tools_1 */
void      init_mat_zero(t_mat4x4 *mat);
t_mat4x4  init_matrotx(float fTheta);
t_mat4x4	init_matroty(float fTheta);
t_mat4x4	init_matrotz(float fTheta);
/* matrice_tools_2 */
t_mat4x4  mat_makeid(void);
t_mat4x4  mat_maketrans(float x, float y, float z);
t_mat4x4  mat_makeproj(float fFov, float fAspectRatio, float fNear, float fFar);
/* matrice_tools_3 */
t_vec3d   mat_mulvec(t_mat4x4 m, t_vec3d i);
t_mat4x4  mat_multmat(t_mat4x4 m1, t_mat4x4 m2);
t_mat4x4  mat_pointat(t_vec3d pos, t_vec3d target, t_vec3d up);
t_mat4x4  mat_quick_invert(t_mat4x4 m);
/* clipping */
int tri_clipping(t_vec3d plane_p, t_vec3d plane_n, t_triangle in_tri, t_triangle *out_tri1, t_triangle *out_tri2);
/* neo_xmp_parser */
t_texture *xpm_parser(t_texture *tex, int nb_tex);
/* neo_xmp_parser_tool_1 */
int  hex_to_dec(char *hex);
void xpm_malloc(t_texture *tex, t_tex_data *data);
/* fill_texture */
void  fill_texture(t_triangle tri, t_texture tex, t_depth *depthbuff);
/* fill_texture_tools_1 */
t_tex_var init_tex_var(t_triangle tri, t_tex_var var);
t_tex_var get_step(t_tex_var var);
t_tex_var init_tex_var_second(t_triangle tri, t_tex_var var);
#endif

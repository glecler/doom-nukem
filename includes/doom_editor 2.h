#ifndef DOOM_EDITOR_H
# define DOOM_EDITOR_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft/ft_printf/srcs/ft_printf.h"
# define NONE 0
# define DRAW_WALL 1
# define DRAW_FLOOR 2
# define ERASE 3
# define MENU 4
# define MENU_FILE 5
# define MENU_DRAW 6
# define MENU_TOOL 7
# define SELECT_NONE 8
# define SELECT_NODE 9
# define DRAW_NONE 10
# define DRAW_NODE 11
# define FAILED_NEW_IMAGE 12
# define FAILED_LIST_ALLOC 13
# define FAILED_NODE_ALLOC 14
# define FAILED_INIT_MLX 15
# define FAILED_NEW_WIN 16
# define FAILED_NEW_TEX 17
# define FAILED_OPEN_FILE 18
# define FAILED_READ_FILE 19
# define FAILED_WRITE_FILE 20
# define FAILED_WRITE_DATA 21
# define FAILED_MALLOC 22
# define FAILED_LINK_ALLOC 24
# define FAILED_TLIST_FILL 25
# define TOOL_LINK_WALL 26
# define TOOL_LINK_FLOOR 27
# define TOOL_AUTO_FLOOR 28
# define FIRST_NODE 29
# define SECOND_NODE 30
# define WALL 31
# define FLOOR 32
# define SELECT 33
# define TOOL_TEXTURES 34
# define TOOL_WEAPONS 35
# define TOP 36
# define TOP_WALL 39
# define TOP_FLOOR_WALL 40
# define FLOOR_WALL 37
# define TOOL_Z 38
# define TOOL_LINK_TOP 41
# define MENU_LINK 42
# define TOP_FLOOR 43
# define ALL 44
# define TEX_CHOOSE 45
# define PROTO_VIO 46
# define PROTO_ORA 47
# define PROTO_VERT 48
# define PROTO_VIOT 49

typedef struct      s_node
{
    double x;
	double y;
	double z;
	int	   type;
}                   t_node;

typedef struct s_coord
{
	double x;
	double y;
}				t_coord;

typedef struct s_segment
{
	t_node a;
	t_node b;
	int 	type;
}				t_segment;

typedef struct s_texture
{
	void 	*img_ptr;
	char 	*img_addr;
	int		sl;
	int 	endian;
	int 	bpp;
}				t_texture;	

typedef struct s_win_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	void				*buff_img_ptr;
	int					bpp;
	int					endian;
	int					size_line;
	char				*addr;
	char				*buff_addr;
	unsigned char		rgb[3];
	unsigned char 		blue[3];
	unsigned char		green[3];
	t_texture			ux_textures[6];
}				t_win_data;

typedef struct s_node_list
{
    t_node				node;
	int 				no;
	int					type;
	int					floor_tex;
	int					top_tex;
	int					wall_tex;
    struct s_node_list	*next;
	struct s_node_list	*prev;
}				t_node_list;

typedef struct  s_list
{
    struct s_node_list	*first;
	int 				list_size;
}               t_list;

typedef struct s_link
{
	t_node_list *node_a;
	t_node_list *node_b;
	int			floor_tex;
	int			top_tex;
	int			wall_tex;
}				t_link;

typedef struct s_link_list
{
	t_link 				link;
	int					type;
	int					active;
	struct s_link_list *next;
	struct s_link_list *prev;
}				t_link_list;

typedef struct s_llist
{
	t_link_list *first;
}				t_llist;

typedef struct s_triangle
{
	int a;
	int b;
	int c;
	int tex;
	int type;
}				t_triangle;

typedef struct s_triangle_list
{
	t_triangle				triangle;
	struct s_triangle_list *next;
	struct s_triangle_list *prev;
}				t_triangle_list;

typedef struct s_tlist
{
	t_triangle_list *first;
}				t_tlist;

typedef struct s_e_data
{
	t_win_data	*win_data;
	int			draw_state;
	t_segment	buff;
	t_list		*list;
	t_llist		*llist;
	t_link		*buff_link;
	int			mode;
	int			select_state;
	int			link_state;
	int			no[4];
	t_node_list *selected_node;
	t_tlist		*tlist;
	int 		display_mode;
	int			curr_tex;
	int			(tex[3])[3];
}				t_e_data;

/*
** main.c
*/

int	    	ft_mlx_win_gen(t_list *list);
int 		ft_map_edit(t_win_data *w_data, t_list *list);

/*
** graphics.c
*/

int			ft_set_rgb_type(unsigned char *rgb, int type, int dmode);
int 		ft_draw_axis(char *addr, unsigned char *rgb, int size_line);
int 		ft_update_map(t_e_data *e_data);
int			ft_display_map(t_e_data *e_data);

/*
** graphics_tools.c
*/

int			ft_big_pixel_img(char *addr, t_node node, unsigned char *rgb, t_e_data *e_data);
int			ft_put_pixel_img(char *addr, int x, int y, unsigned char *rgb);
void 		ft_put_line_vert(t_node a, t_node b, char *addr, t_e_data *data);
void 		ft_put_line_img(t_node a, t_node b, char *addr, t_e_data *data);
void		ft_flush_img(char **addr);

/*
** list.c
*/

int    		ft_add_to_list(t_node node, t_list *list);
void		ft_delete_node(t_node_list *node, t_list *list);
int			ft_free_list(t_list *list);
int			ft_set_node_list(t_node node, t_node_list *buff);

/*
** llist.c
*/

void    	ft_delete_link(t_link_list *link, t_llist *llist);
int    		ft_add_to_llist(t_link link, t_llist *llist, int type);
int 		ft_free_llist(t_llist *llist);
int			ft_set_link_list(t_link_list *buff, t_link link, int type);

/*
** events.c
*/

int			ft_get_motion(int x, int y, t_e_data *e_data);
int 		ft_get_mouse(int button, int x, int y, t_e_data *e_data);
int			ft_get_key(int key, t_e_data *e_data);

/*
** choose_mode.c
*/

int			ft_tool_choose_mode(int button, int x, int y, t_e_data *e_data);
int			ft_draw_choose_mode(int button, int x, int y, t_e_data *e_data);
int			ft_menu_choose_mode(int x, int y, t_e_data *e_data);
int			ft_banner_choose(int tex, int x, int type, t_e_data *e_data);

/*
** tools.c
*/

void		ft_coord_swap(t_node *a, t_node *b);
t_node		ft_create_node(double x, double y, double z, int type);
void		ft_error(int errno);
t_link		ft_set_link(t_node_list *a, t_node_list *b);

/*
** link_tools.c
*/

int			ft_delete_last_link(t_llist *llist);
int			ft_delete_links_node(t_node_list *buff, t_llist *llist);
t_node_list *ft_last_node(t_list *list);
t_node_list	*ft_selected_node(int x, int y, t_e_data *e_data);

/*
** init_tools.c
*/

int     	ft_init_win_data(t_win_data *win_data);
int 		ft_init_editor_data(t_e_data *_data, t_win_data *w_data, t_list *list, t_llist *llist);
void		ft_set_rgb(unsigned char *rgb, int r, int g, int b);
t_node		ft_set_node(t_node node, int x, int y, int z);
int 		ft_init_textures(t_win_data *w_data);


/*
** intersect.c
*/
int			ft_intersect_all_llist(t_llist *llist);
int			ft_intersect_llist(t_segment buff, t_llist *llist);
int 		ft_intersect(t_segment buff, t_segment list);
int 		ft_find_orientation(t_node x, t_node y, t_node z);
int 		ft_on_segment(t_node x, t_node y, t_node z);

/*
** button_draw.c
*/

int			ft_button_draw_mode_wall(int button, int x, int y, t_e_data *e_data);
int			ft_button_draw_mode_floor(int button, int x, int y, t_e_data *e_data);
int			ft_button_draw_mode_top(int button, int x, int y, t_e_data *e_data);

/*
** draw_mode_clic.c
*/

int			ft_but_d_mode_rgt_clk(int x, int y, t_e_data *e_data, int type);
int			ft_but_d_mode_lft_clk(int x, int y, t_e_data *e_data, int type);
int			ft_but_d_mode_lft_clkn(int x, int y, t_e_data *e_data, int type);

/*
** button_select.c
*/

int 		ft_button_select_mode(int button, int x, int y, t_e_data *e_data);
int 		ft_button_select_mode_node(t_e_data *e_data);
int 		ft_button_select_mode_none(int x, int y, t_e_data *e_data);

/*
** button_erase.c
*/

int 		ft_button_erase_mode(int button, int x, int y, t_e_data *e_data);

/*
** button_link.c
*/

int 		ft_type(int type, int added_type);
int 		ft_button_link_second_node(t_e_data *e_data, t_node_list *buff, int type);
int 		ft_button_link_mode_top(int button, int x, int y, t_e_data *e_data);
int			ft_button_link_mode_wall(int button, int x, int y, t_e_data *e_data);
int			ft_button_link_mode_floor(int button, int x, int y, t_e_data *e_data);

/*
** mode.c
*/

int			ft_tool_interact(int x, int y, t_e_data *e_data);
int 		ft_banner_interact(int x, int y, t_e_data *e_data);
int			ft_link_interact(int x, int y, t_e_data *e_data);
int 		ft_mode_interact(int x, int y, t_e_data *e_data);
int 		ft_file_interact(int x, int y, t_e_data *e_data);

/*
** motion.c
*/

int			ft_motion_select_mode(int x, int y, t_e_data *e_data);
int 		ft_motion_draw_mode(int x, int y, t_e_data *e_data, int type);

/*
** file.c
*/ 

int			ft_new_file(t_e_data *e_data);
int 		ft_export_file(t_e_data *e_data);
int			ft_export_data_to_save(t_e_data *e_data, int fd);
char		*ft_join_mtl(char *data);

/*
** triangle.c
*/

int 		ft_link_to_triangle(t_tlist *tlist, t_e_data *e_data);
int 		ft_fill_tlist(t_tlist *tlist, t_e_data *e_data);
t_tlist		*ft_create_triangles(t_e_data *e_data);

/*
** triangle_tools.c
*/

int 		ft_clean_triangles(t_tlist *tlist);
int 		ft_is_tri_equal(t_triangle tri1, t_triangle tri2);
t_triangle	ft_create_triangle(int a, int b, int c);
int 		ft_assign_number(t_list *list);
int 		ft_init_llist_active(t_llist *llist);

/*
** triangulate.c
*/

int			ft_add_top_link(t_node_list *node, t_e_data *e_data);
int			ft_add_floor_link(t_node_list *node, t_e_data *e_data);
int 		ft_triangulate_polygon_top(t_e_data *e_data);
int 		ft_triangulate_polygon_floor(t_e_data *e_data);
int 		ft_node_from_node(t_node_list *node, t_node_list *goal, t_e_data *e_data);

/*
** recursive_triangle.c
*/

int			ft_add_triangle_floor(t_node_list *node, t_link_list *buff,	int no[4], t_e_data *e_data);
int			ft_add_triangle_top(t_node_list *node, t_link_list *buff, int no[4], t_e_data *e_data);
int 		ft_triangle_from_node_floor(t_node_list *node, int vertex, t_e_data *e_data, int no[4]);
int 		ft_triangle_from_node_top(t_node_list *node, int vertex, t_e_data *e_data, int no[4]);

/*
** tlist.c
*/

int		    ft_add_to_tlist(t_triangle triangle, t_tlist *tlist, int tex);
int 		ft_print_tlist(t_tlist *tlist);
void   	 	ft_delete_triangle(t_triangle_list *triangle, t_tlist *tlist);
int			ft_set_triangle_list(t_triangle triangle, int tex, t_triangle_list *buff);
int			ft_free_tlist(t_tlist *tlist);

/*
** clean_links.c
*/

int			ft_clean_links(t_llist *llist);
int 		ft_delete_link_type(t_link_list *link, t_link_list *buff, t_llist *llist);

/*
** export_file.c
*/

char 		*ft_export_v(t_e_data *e_data, char *data);
char 		*ft_export_walls(t_e_data *e_data, char *data);
char 		*ft_export_floor_top(t_e_data *e_data, char *data);
char		*ft_xpm_tex(int tex_code);

/*
** button_texture.c
*/

int 		ft_choose_texture(int x, int y, t_e_data *e_data);
int 		ft_button_textures(int button, int x, int y, t_e_data *e_data);
int 		ft_type_display(int type, int dmode);
t_link_list	*ft_selected_link(t_e_data *e_data);

/*
** tex_choose.c
*/

int			ft_assign_tex_tri(int *tex, t_link_list *link);
int			ft_tex_choose_tri_floor(t_e_data *e_data);
int			ft_tex_choose_tri_top(t_e_data *e_data);

/*
** delete_links.c
*/

int			ft_delete_4_links(t_link_list *link, t_link_list *buff, t_llist *llist);
int			ft_delete_5_links(t_link_list *link, t_link_list *buff, t_llist *llist);
int 		ft_delete_3_links(t_link_list *link, t_link_list *buff, t_llist *llist);
int 		ft_delete_1_links(t_link_list *link, t_link_list *buff, t_llist *llist);
int 		ft_delete_2_links(t_link_list *link, t_link_list *buff, t_llist *llist);

/*
** wall_strjoin.c
*/

char		*ft_wall_strjoin1(t_link_list *link_buff, char *data);
char		*ft_wall_strjoin2(t_link_list *link_buff, char *data);
char		*ft_tri_strjoin(t_triangle_list *t_buff, char *data);



#endif
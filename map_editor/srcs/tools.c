#include "../includes/doom_editor.h"

void ft_error(int errno)
{
    if (errno == FAILED_NEW_IMAGE)
        printf("error : image creation failed\n");
    if (errno == FAILED_LIST_ALLOC)
        printf("error : list allocation failed\n");
   if (errno == FAILED_INIT_MLX)
        printf("error : MLX initialisation failed\n");
    if (errno == FAILED_NEW_WIN)
        printf("error : window creation failed\n");
    if (errno == FAILED_NEW_TEX)
        printf("error : texture image creation failed\n");
    if (errno == FAILED_MALLOC)
        printf("error : memory allocation failed\n");
    if (errno == FAILED_READ_FILE)
        printf("error : reading file failed\n");
    if (errno == FAILED_OPEN_FILE)
        printf("error : opening file failed\n");
    if (errno == FAILED_WRITE_FILE)
        printf("error : writing to file failed\n");
    if (errno == FAILED_WRITE_DATA)
        printf("error : saving data failed\n");
    if (errno == FAILED_SAVE_OVERFLOW)
        printf("error : too many saves\n");
    if (errno == FAILED_NODE_ALLOC)
        printf("error : node allocation failed\n");
    exit (0);
}

t_node ft_create_node(double x, double y, double z, int type)
{
    t_node node;

    node.x = x;
    node.y = y;
    node.z = z;
    node.type = type;
    return (node);
}

void	ft_coord_swap(t_node *a, t_node *b)
{
	a->x += b->x;
	b->x = a->x - b->x;
	a->x -= b->x;
	a->y += b->y;
	b->y = a->y - b->y;
	a->y -= b->y;
    a->z += b->z;
	b->z = a->z - b->z;
	a->z -= b->z;
}

t_link ft_set_link(t_node_list *a, t_node_list *b)
{
    t_link link;

    link.node_a = a;
    link.node_b = b;
    return (link);
}
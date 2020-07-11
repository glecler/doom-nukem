#include "../includes/doom_editor.h"

void    ft_delete_triangle(t_triangle_list *triangle, t_tlist *tlist)
{   
    if (triangle->next == NULL && triangle->prev == NULL)
    {
        tlist->first = NULL;
        free(triangle);
    }
    else if (triangle->next == NULL && triangle->prev != NULL)
    {
        triangle->prev->next = NULL;
        free(triangle);
    }
    else if (triangle->prev == NULL && triangle->next != NULL)
    {
        tlist->first = triangle->next;
        triangle->next->prev = NULL;
        free(triangle);
    }
    else
    {
        triangle->next->prev = triangle->prev;
        triangle->prev->next = triangle->next;
        free(triangle);        
    }
}

int    ft_add_to_tlist(t_triangle triangle, t_tlist *tlist, int tex)
{
    t_triangle_list *buff;

    buff = tlist->first;
    if (buff == NULL)
    {
        if (!(buff = (t_triangle_list*)malloc(sizeof(t_triangle_list))))
            ft_error(FAILED_MALLOC);
        buff->triangle = triangle;
        buff->triangle.tex = tex;
        buff->next = NULL;
        buff->prev = NULL;
        tlist->first = buff;
        return (0);
    }
    else
    {    
        while (buff->next != NULL)
           buff = buff->next;
        if (!(buff->next = (t_triangle_list*)malloc(sizeof(t_triangle_list))))
            ft_error(FAILED_MALLOC);       
        buff->next->triangle = triangle;
        buff->next->triangle.tex = tex;
        buff->next->next = NULL;
        buff->next->prev = buff;
        buff->next->prev->next = buff->next;
    }
    return (0);
}

int ft_print_tlist(t_tlist *tlist)
{
    t_triangle_list *buff;
    int i;

    i = 0;
    buff = tlist->first;
    printf("~~~~~~ triangle LIST ~~~~~~~~\n\n");
    while (buff)
    {
        printf("  triangle : [%d]\n", i);
        printf("  a    : [%d]\n", buff->triangle.a);
        printf("  b    : [%d]\n\n", buff->triangle.b);
        printf("  c    : [%d]\n\n", buff->triangle.c);
        printf("  tex  : [%d]\n", buff->triangle.tex);
        if (buff->next == NULL)
            printf("last node!\n");
        i++;
        buff = buff->next;
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~\n");
    return (0);
}
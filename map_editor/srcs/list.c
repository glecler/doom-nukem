#include "../includes/doom_editor.h"

void    ft_delete_node(t_node_list *node, t_list *list)
{   
    if (node->next == NULL && node->prev == NULL)
    {
        list->first = NULL;
        free(node);
    }
    else if (node->next == NULL && node->prev != NULL)
    {
        node->prev->next = NULL;
        free(node);
    }
    else if (node->prev == NULL && node->next != NULL)
    {
        list->first = node->next;
        node->next->prev = NULL;
        free(node);
    }
    else
    {
        node->next->prev = node->prev;
        node->prev->next = node->next;
        free(node);        
    }
    list->list_size -= 1;
}

int    ft_add_to_list(t_node node, t_list *list)
{
    t_node_list *buff;

    buff = list->first;
    if (buff == NULL)
    {
        if (!(buff = (t_node_list*)malloc(sizeof(t_node_list))))
            ft_error(FAILED_NODE_ALLOC);
        buff->node = node;
        buff->next = NULL;
        buff->prev = NULL;
        buff->floor_tex = NONE;
        buff->top_tex = NONE;
        buff->wall_tex = NONE;
        list->first = buff;
        return (0);
    }
    else
    {    
        while (buff->next != NULL)
           buff = buff->next;
        if (!(buff->next = (t_node_list*)malloc(sizeof(t_node_list))))
            ft_error(FAILED_NODE_ALLOC);       
        buff->next->node = node;
        buff->floor_tex = NONE;
        buff->top_tex = NONE;
        buff->wall_tex = NONE;
        buff->next->next = NULL;
        buff->next->prev = buff;
        buff->next->prev->next = buff->next;
    }
    list->list_size += 1;
    return (0);
}

int ft_print_list(t_list *list)
{
    t_node_list *buff;
    int i;

    i = 0;
    buff = list->first;
    printf("~~~~~~ NODE LIST ~~~~~~~~\n\n");
    while (buff)
    {
        printf("  node : [%d]\n", i);
        printf("number : [%d]", buff->no);
        printf("  x    : [%.0f]\n", buff->node.x);
        printf("  y    : [%.0f]\n\n", buff->node.y);
        printf("type   : [%d]\n", buff->node.type);
        if (buff->next == NULL)
            printf("last node!\n");
        i++;
        buff = buff->next;
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~\n");
    return (0);
}

int ft_free_list(t_list *list)
{
    t_node_list *buff;
    t_node_list *del_buff;

    buff = list->first;
    while (buff)
    {   
        del_buff = buff;
        ft_delete_node(del_buff, list);
        buff = buff->next;
    }
    free(list);
    return (0);
}
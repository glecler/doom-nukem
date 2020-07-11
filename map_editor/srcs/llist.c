#include "../includes/doom_editor.h"

void    ft_delete_link(t_link_list *link, t_llist *llist)
{   
    if (link->next == NULL && link->prev == NULL)
    {
        llist->first = NULL;
        free(link);
    }
    else if (link->next == NULL && link->prev != NULL)
    {
        link->prev->next = NULL;
        free(link);
    }
    else if (link->prev == NULL && link->next != NULL)
    {
        llist->first = link->next;
        link->next->prev = NULL;
        free(link);
    }
    else
    {
        link->next->prev = link->prev;
        link->prev->next = link->next;
        free(link);        
    }
}

int    ft_add_to_llist(t_link link, t_llist *llist, int type)
{
    t_link_list *buff;

    buff = llist->first;
    if (buff == NULL)
    {
        if (!(buff = (t_link_list*)malloc(sizeof(t_link_list))))
            ft_error(FAILED_NODE_ALLOC);
        buff->link = link;
        buff->active = 0;
        buff->type = type;
        buff->next = NULL;
        buff->prev = NULL;
        llist->first = buff;
        return (0);
    }
    else
    {    
        while (buff->next != NULL)
           buff = buff->next;
        if (!(buff->next = (t_link_list*)malloc(sizeof(t_link_list))))
            ft_error(FAILED_LINK_ALLOC);       
        buff->next->link = link;
        buff->next->active = 0;
        buff->next->type = type;       
        buff->next->next = NULL;
        buff->next->prev = buff;
        buff->next->prev->next = buff->next;
    }
    return (0);
}

int ft_free_llist(t_llist *llist)
{
    t_link_list *buff;
    t_link_list *del_buff;

    buff = llist->first;
    while (buff)
    {   
        del_buff = buff;
        ft_delete_link(del_buff, llist);
        buff = buff->next;
    }
    free(llist);
    return (0);
}
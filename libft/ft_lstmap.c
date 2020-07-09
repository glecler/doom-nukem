/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:28:06 by ravernhe          #+#    #+#             */
/*   Updated: 2019/11/30 17:28:58 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list	*elem))
{
	t_list	*new;
	t_list	*cpy;
	t_list	*first;

	if (!lst)
		return (NULL);
	cpy = f(lst);
	if (!(new = ft_lstnew(cpy->content, cpy->content_size)))
		return (NULL);
	first = new;
	lst = lst->next;
	while (lst)
	{
		cpy = f(lst);
		if ((new->next = ft_lstnew(cpy->content, cpy->content_size)) == NULL)
			return (NULL);
		new = new->next;
		lst = lst->next;
	}
	return (first);
}

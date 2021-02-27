/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:13:11 by jdanelon          #+#    #+#             */
/*   Updated: 2020/01/30 15:16:44 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*element;

	if (del == 0)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		element = *lst;
		*lst = element->next;
		free(element);
	}
	*lst = NULL;
}

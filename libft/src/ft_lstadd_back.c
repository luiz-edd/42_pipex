/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 11:26:31 by leduard2          #+#    #+#             */
/*   Updated: 2023/08/02 17:01:31 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

	p = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (p)
	{
		if (p->next == NULL)
		{
			p->next = new;
			return ;
		}
		p = p->next;
	}
}

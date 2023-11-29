/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:27:06 by leduard2          #+#    #+#             */
/*   Updated: 2023/07/25 14:36:17 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	val;

	p = (unsigned char *)s;
	val = (unsigned char)c;
	i = 0;
	while (n > 0)
	{
		p[i] = val;
		i++;
		n--;
	}
	return (p);
}

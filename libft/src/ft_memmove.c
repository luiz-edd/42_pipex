/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:44:12 by leduard2          #+#    #+#             */
/*   Updated: 2023/08/10 18:28:48 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*udest;
	unsigned char	*usrc;

	i = 0;
	udest = (unsigned char *)dest;
	usrc = (unsigned char *)src;
	if (!udest && !usrc)
		return (0);
	if (udest < usrc)
	{
		while (i < n)
		{
			udest[i] = usrc[i];
			i++;
		}
		return (udest);
	}
	i = n - 1;
	while (i < n)
	{
		udest[i] = usrc[i];
		i--;
	}
	return (udest);
}

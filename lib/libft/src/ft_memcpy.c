/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:37:16 by leduard2          #+#    #+#             */
/*   Updated: 2023/08/08 15:19:49 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*usrc;
	unsigned char	*udest;

	i = 0;
	usrc = (unsigned char *)src;
	udest = (unsigned char *)dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		udest[i] = usrc[i];
		i++;
	}
	return (udest);
}

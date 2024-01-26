/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:54:49 by leduard2          #+#    #+#             */
/*   Updated: 2023/07/24 13:03:56 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	char	*c;
	int		i;
	int		sign;
	int		sum;

	i = 0;
	sign = 1;
	c = (char *)nptr;
	sum = 0;
	while ((c[i] >= '\t' && c[i] <= '\r') || c[i] == ' ')
		i++;
	if (c[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (c[i] == '+')
		i++;
	while (ft_isdigit(c[i]))
	{
		sum = (sum * 10) + (c[i] - '0');
		i++;
	}
	return (sum * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:44:08 by leduard2          #+#    #+#             */
/*   Updated: 2023/11/21 15:57:45 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_blank(char str)
{
	if (str <= 32)
		return (1);
	return (0);
}

int	is_valid_char(char c, int base)
{
	char	*hexa;
	char	*hexa1;

	hexa = "0123456789abcdef";
	hexa1 = "0123456789ABCDEF";
	while (base--)
	{
		if (hexa[base] == c || hexa1[base] == c)
			return (1);
	}
	return (0);
}

int	value_in_decimal(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

unsigned int	ft_atoi_base(char *str, int base)
{
	unsigned int	num;
	int				sign;
	int				i;

	sign = 1;
	num = 0;
	i = 0;
	while (is_blank(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (is_valid_char(str[i], base))
		num = (num * base) + (value_in_decimal(str[i++]));
	return (num * sign);
}

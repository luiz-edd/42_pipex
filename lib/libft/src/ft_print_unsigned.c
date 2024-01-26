/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:19:04 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/19 19:43:03 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_unsigned_formated(unsigned long n)
{
	int		count;
	char	aux;

	count = 0;
	if (n <= 9)
	{
		aux = (n + '0');
		return (write(1, &aux, 1));
	}
	else
	{
		count = ft_print_unsigned_formated(n / 10);
		return (count + ft_print_unsigned_formated(n % 10));
	}
}

int	ft_print_unsigned(t_format *flags)
{
	int		count;
	long	n;

	count = 0;
	n = (unsigned long)va_arg(flags->ap, unsigned int);
	if (n >= 0)
	{
		if (flags->sign >= 1 && n > 0)
			count += write(1, "+", 1);
		else if (flags->sp >= 1)
			count += write(1, " ", 1);
	}
	return (count + ft_print_unsigned_formated(n));
}

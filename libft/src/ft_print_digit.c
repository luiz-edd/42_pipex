/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:46:31 by leduard2          #+#    #+#             */
/*   Updated: 2023/11/21 17:12:26 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_digit_formated(long n)
{
	int		count;
	char	aux;

	count = 0;
	if (n < 0)
		return (write(1, "-", 1) + ft_print_digit_formated(-n));
	else if (n <= 9)
	{
		aux = (n + '0');
		return (write(1, &aux, 1));
	}
	else
	{
		count = ft_print_digit_formated((n / 10));
		return (count + ft_print_digit_formated(n % 10));
	}
}

int	ft_print_digit(t_format *flags)
{
	int		count;
	long	n;

	count = 0;
	n = (long)va_arg(flags->ap, int);
	if (n >= 0)
	{
		if (flags->sign >= 1 && n >= 0)
			count += write(1, "+", 1);
		else if (flags->sp >= 1)
			count += write(1, " ", 1);
	}
	return (count + ft_print_digit_formated(n));
}

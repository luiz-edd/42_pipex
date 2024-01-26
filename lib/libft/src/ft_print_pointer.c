/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:47:28 by leduard2          #+#    #+#             */
/*   Updated: 2023/11/21 17:12:45 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_pointer_formated(unsigned long n, int base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (n < (unsigned long)base)
		return (write(1, &symbols[n], 1));
	else
	{
		count = ft_print_pointer_formated(n / base, base);
		return (count + ft_print_pointer_formated(n % base, base));
	}
}

int	ft_print_pointer(t_format *flags)
{
	unsigned long	n;

	n = (unsigned long)va_arg(flags->ap, unsigned long);
	if (n == 0)
		return (write(1, "(nil)", 5));
	return (write(1, "0x", 2) + ft_print_pointer_formated(n, 16));
}

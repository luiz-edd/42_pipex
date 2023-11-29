/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ex_up.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:47:28 by leduard2          #+#    #+#             */
/*   Updated: 2023/11/21 17:12:33 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ex_up_formated(long n, int base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789ABCDEF";
	if (n < 0)
		return (ft_print_ex_up_formated(-n, base) + write(1, "-", 1));
	else if (n < base)
		return (write(1, &symbols[n], 1));
	else
	{
		count = ft_print_ex_up_formated(n / base, base);
		return (count + ft_print_ex_up_formated(n % base, base));
	}
}

int	ft_print_ex_up(t_format *flags)
{
	unsigned int	n;
	int				count;

	n = (unsigned int)va_arg(flags->ap, int);
	count = 0;
	if (flags->hash >= 1 && n != 0)
		count += write(1, "0X", 2);
	return (count + ft_print_ex_up_formated(n, 16));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:17:45 by leduard2          #+#    #+#             */
/*   Updated: 2023/08/08 15:26:41 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = n;
	if (num < 0)
	{
		num *= -1;
		ft_putchar_fd('-', fd);
	}
	if (num > 9)
	{
		ft_putnbr_fd((int)(num / 10), fd);
		ft_putchar_fd(num % 10 + '0', fd);
	}
	else
	{
		ft_putchar_fd(num % 10 + '0', fd);
	}
}

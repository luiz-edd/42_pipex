/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:16:40 by leduard2          #+#    #+#             */
/*   Updated: 2023/12/04 11:24:06 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_words(char **str)
{
	int i;
	i = 0;

	while (str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
}
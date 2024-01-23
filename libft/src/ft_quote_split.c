/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:04:17 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/19 20:25:31 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_quote_split(char *str, char delimiter)
{
	char	**arr;
	int		i;
	int		words;

	i = -1;
	words = ft_countwords_quote(str, delimiter);
	ft_printf("str:|%s|\n", str);
	ft_printf("total words: %d\n", words);
	arr = (char **)malloc((words + 1) * sizeof(char *));
	while (++i < words)
	{
		ft_printf("----------------------------------------\n");
		ft_printf("len: %d\n", ft_get_len(str, delimiter));
		arr[i] = (char *)malloc(ft_get_len(str, delimiter) + 1);
		ft_add_word(str, delimiter, arr[i]);
		ft_printf("position: %d\nword:|%s|\n", i, arr[i]);
		str = ft_move_next_word(str, delimiter);
	}
	return (arr);
}

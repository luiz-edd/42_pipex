/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_count_words.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:39:05 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/19 20:24:18 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_is_a_word(char *str, char delimiter, char quote, int *count)
{
	while (*str != quote && *str != '\0')
		str++;
	if (*str != '\0')
	{
		str++;
		if (*str == delimiter)
		{
			*count += 1;
			while (*str == delimiter)
				str++;
		}
		else if (*str == '\0')
			*count += 1;
	}
	else
		*count += 1;
	return (str);
}

static char	*verify_word(char *str, char delimiter, char quote, int *count)
{
	while (*str == delimiter)
		str++;
	if (*str == quote)
	{
		str++;
		if (*str == quote)
		{
			str++;
			if (*str == '\0' || *str == delimiter)
				*count += 1;
		}
		else
			str = ft_is_a_word(str, delimiter, quote, count);
	}
	return (str);
}

//  ""''aa
int	ft_countwords_quote(char *str, char delimiter)
{
	int	count;

	count = 0;
	while (*str)
	{
		str = verify_word(str, delimiter, S_QUOTE, &count);
		str = verify_word(str, delimiter, D_QUOTE, &count);
		while (*str != S_QUOTE && *str != D_QUOTE && *str && *str != delimiter)
		{
			str++;
			if (*str == '\0' || *str == delimiter)
				count++;
		}
	}
	return (count);
}

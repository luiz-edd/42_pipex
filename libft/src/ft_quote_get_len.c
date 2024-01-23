/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_get_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:23:32 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/19 20:10:56 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*move_quote(char *str, char quote, int *end_word, int *len)
{
	if (*str == quote)
	{
		str++;
		if (*str == quote)
			str++;
		else
		{
			*end_word = 1;
			while (*str != quote && *str != '\0')
			{
				*len += 1;
				str++;
			}
			if (*str != '\0')
				str++;
		}
	}
	return (str);
}

static char	*ft_move_delimiter(char *str, char delimiter)
{
	while (*str == delimiter)
		str++;
	return (str);
}

static char	*ft_not_quote(char *str, char delimiter, int *len, int *end_word)
{
	while (*str != S_QUOTE && *str != D_QUOTE && *str != delimiter
		&& *str != '\0')
	{
		str++;
		*len += 1;
	}
	*end_word = 1;
	return (str);
}

int	ft_get_len(char *str, char delimiter)
{
	int	end_word;
	int	len;

	end_word = 0;
	len = 0;
	str = ft_move_delimiter(str, delimiter);
	while (!end_word)
	{
		if (*str == S_QUOTE)
			str = move_quote(str, S_QUOTE, &end_word, &len);
		else if (*str == D_QUOTE)
			str = move_quote(str, D_QUOTE, &end_word, &len);
		else
			str = ft_not_quote(str, delimiter, &len, &end_word);
		if (!(*str == delimiter || *str == '\0'))
			end_word = 0;
	}
	str = ft_move_delimiter(str, delimiter);
	return (len);
}

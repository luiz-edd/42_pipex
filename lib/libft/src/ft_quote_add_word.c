/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_add_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:23:32 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/19 19:55:02 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*move_s_quote(char *str, char *dst, int *end_word, int *i)
{
	if (*str == S_QUOTE)
	{
		str++;
		if (*str == S_QUOTE)
			str++;
		else
		{
			*end_word = 1;
			while (*str != S_QUOTE && *str != '\0')
			{
				dst[*i] = *str;
				*i += 1;
				str++;
			}
			if (*str != '\0')
				str++;
		}
	}
	return (str);
}

static char	*move_d_quote(char *str, char *dst, int *end_word, int *i)
{
	if (*str == D_QUOTE)
	{
		str++;
		if (*str == D_QUOTE)
			str++;
		else
		{
			*end_word = 1;
			while (*str != D_QUOTE && *str != '\0')
			{
				dst[*i] = *str;
				*i += 1;
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

static void	ft_not_end_word(char *str, char delimiter, int *end_word)
{
	if (!(*str == delimiter || *str == '\0'))
		*end_word = 0;
}

void	ft_add_word(char *str, char delimiter, char *dst)
{
	int	end_word;
	int	i;

	end_word = 0;
	i = 0;
	str = ft_move_delimiter(str, delimiter);
	while (!end_word)
	{
		if (*str == S_QUOTE)
			str = move_s_quote(str, dst, &end_word, &i);
		else if (*str == D_QUOTE)
			str = move_d_quote(str, dst, &end_word, &i);
		else
		{
			while (*str != S_QUOTE && *str != D_QUOTE && *str != delimiter
				&& *str != '\0')
			{
				dst[i++] = *str;
				str++;
			}
			end_word = 1;
		}
		ft_not_end_word(str, delimiter, &end_word);
	}
	dst[i] = '\0';
}

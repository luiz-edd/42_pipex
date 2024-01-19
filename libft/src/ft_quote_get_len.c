/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_get_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:23:32 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/19 18:11:08 by leduard2         ###   ########.fr       */
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

//"\'\'\'  \'\'\' fds\'\'    \'\"ds\'"
int	ft_get_len(char *str, char delimiter)
{
	int end_word;
	int len;
	end_word = 0;
	len = 0;
	while (*str == delimiter)
		str++;
	while (!end_word)
	{
		if (*str == S_QUOTE)
			str = move_quote(str, S_QUOTE, &end_word, &len);
		else if (*str == D_QUOTE)
			str = move_quote(str, D_QUOTE, &end_word, &len);
		else
		{
			while (*str != S_QUOTE && *str != D_QUOTE && *str != delimiter
				&& *str != '\0')
			{
				str++;
				len += 1;
			}
			end_word = 1;
		}
		if (!(*str == delimiter || *str == '\0'))
			end_word = 0;
	}
	while (*str == delimiter)
		str++;
	return (len);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:01:23 by leduard2          #+#    #+#             */
/*   Updated: 2023/08/03 17:51:45 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		s1_len;
	const char	*s1_last;
	char		*str;

	s1_len = ft_strlen(s1);
	s1_last = &s1[s1_len - 1];
	while (ft_strchr(set, *s1) && *s1)
	{
		s1++;
	}
	while (ft_strchr(set, *s1_last) && *s1_last)
	{
		s1_last--;
	}
	str = ft_substr(s1, 0, ft_strlen(s1) - ft_strlen(s1_last) + 1);
	return (str);
}

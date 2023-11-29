/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:41:39 by leduard2          #+#    #+#             */
/*   Updated: 2023/10/21 18:41:46 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_wordcount(char *str, char delimiter)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != delimiter)
		{
			count++;
			while (str[i] != delimiter && str[i])
			{
				i++;
			}
		}
		if (str[i])
			i++;
	}
	return (count);
}

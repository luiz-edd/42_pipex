/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:04:34 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/19 20:29:04 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/libft.h"

int	main(void)
{
	int i;
	i = -1;
	char *str = " 1 '' \"\" ' \"\" 4'         '         5       ' \"6''''\" 7''\"\"";
	char **splited = ft_quote_split(str, ' ');
	// ft_print_words(splited);
	while (splited[++i])
	{
		free(splited[i]);
	}
	free(splited);
	// ft_printf("position: %d\n%s\n", i, splited[i]);
}
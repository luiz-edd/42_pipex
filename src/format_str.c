/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:43:44 by leduard2          #+#    #+#             */
/*   Updated: 2023/12/04 17:39:47 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(t_pipex *pipex)
{
	int i;
	char **envp;

	envp = pipex->envp;
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			return(envp[i]);
		i++;
	}
	return (NULL);
}



int format_str(t_pipex *pipex)
{
	char *path;
	int i;
	
	i = -1;
	path = get_path(pipex);
	if(path == NULL)
	{
		ft_printf("PATH NOT FOUND\n");
		return (0);
	}
	while (*path != '=')
		path++;
	path++;
	
	pipex->paths = ft_split(path,':');
	while (pipex->paths[++i])
		pipex->paths[i] = ft_strjoin(pipex->paths[i],"/");
	// ft_print_words(pipex->paths);
	return (1);
}

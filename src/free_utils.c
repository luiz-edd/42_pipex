/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:58:02 by leduard2          #+#    #+#             */
/*   Updated: 2023/12/05 19:28:28 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h";

void	*free_pipex(t_tube *tube, t_cmd **cmd, t_pipex *pipex)
{
	int	i;
	int	cmd_quantity;

	i = 0;
	cmd_quantity = pipex->cmd_quantity;
	if (cmd != NULL)
	{
		while (i < cmd_quantity)
		{
			free(cmd[i]);
			cmd[i++] = NULL;
		}
		free(cmd);
		cmd = NULL;
	}
	if (tube != NULL)
	{
		free(tube);
		tube = NULL;
	}
	if (pipex != NULL)
	{
		free(pipex);
		pipex = NULL;
	}
	return (NULL);
}

void	*free_matrix(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
	return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:58:02 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/12 12:24:13 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*free_cmd_content(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_quantity)
	{
		if (pipex->cmd[i]->cmd_path != NULL)
			free(pipex->cmd[i]->cmd_path);
		if (pipex->cmd[i]->cmd_args != NULL)
			free_matrix(pipex->cmd[i]->cmd_args);
		pipex->cmd[i]->cmd_args = NULL;
		pipex->cmd[i]->cmd_path = NULL;
		i++;
	}
	return (NULL);
}

static void	free_tube_and_pipex(t_pipex *pipex, t_tube *tube)
{
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
}

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
			if (cmd[i] != NULL)
				free(cmd[i]);
			cmd[i++] = NULL;
		}
		free(cmd);
		cmd = NULL;
	}
	free_tube_and_pipex(pipex, tube);
	return (NULL);
}

void	*free_matrix(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return (NULL);
}

int	free_finish(t_pipex *pipex)
{
	close_pipes(pipex);
	if (pipex->fd1 >= 0)
		close(pipex->fd1);
	if (pipex->fd2 >= 0)
		close(pipex->fd2);
	free_cmd_content(pipex);
	free_matrix(pipex->paths);
	free_pipex(pipex->tube, pipex->cmd, pipex);
	return (2);
}

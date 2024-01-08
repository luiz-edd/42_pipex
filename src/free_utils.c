/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:58:02 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/08 16:52:35 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h";

void	*free_cmd_content(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_quantity)
	{
		free(pipex->cmd[i]->cmd_path);
		free_matrix(pipex->cmd[i]->cmd_args);
		// pipex->cmd[i]->cmd_args = NULL;
		// pipex->cmd[i]->cmd_path = NULL;
		i++;
	}
	return (NULL);
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
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
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
	close(pipex->fd1);
	close(pipex->fd2);
	free_cmd_content(pipex);
	free_matrix(pipex->paths);
	free_pipex(pipex->tube, pipex->cmd, pipex);
	return (2);
}
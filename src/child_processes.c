/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:11:02 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/26 11:07:46 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	manage_child(t_pipex *pipex, int cmd_position, int pipe_position)
{
	if (cmd_position == 0)
		child_first(pipex, cmd_position, pipe_position);
	else
		child_last(pipex, cmd_position, pipe_position);
}

void	child_first(t_pipex *pipex, int cmd_position, int pipe_position)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = pipex->cmd[cmd_position]->cmd_path;
	cmd_args = pipex->cmd[cmd_position]->cmd_args;
	close(pipex->tube[pipe_position].read_end);
	if (pipex->fd1 < 0)
	{
		free_finish(pipex);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->fd1, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipex->tube[pipe_position].write_end, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	execve(cmd_path, cmd_args, pipex->envp);
	free_finish(pipex);
	exit(EXIT_FAILURE);
}

void	child_last(t_pipex *pipex, int cmd_position, int pipe_position)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = pipex->cmd[cmd_position]->cmd_path;
	cmd_args = pipex->cmd[cmd_position]->cmd_args;
	if (pipex->fd2 < 0)
	{
		free_finish(pipex);
		exit(EXIT_FAILURE);
	}
	close(pipex->tube[cmd_position].write_end);
	if (dup2(pipex->tube[pipe_position - 1].read_end, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipex->fd2, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(pipex->fd2);
	execve(cmd_path, cmd_args, pipex->envp);
	free_finish(pipex);
	exit(EXIT_FAILURE);
}

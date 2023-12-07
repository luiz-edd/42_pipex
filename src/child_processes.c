/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:11:02 by leduard2          #+#    #+#             */
/*   Updated: 2023/12/05 19:16:25 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <stdio.h>

void	child_first(t_pipex *pipex, int cmd_position)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = pipex->cmd[cmd_position]->cmd_path;
	cmd_args = pipex->cmd[cmd_position]->cmd_args;
	close(pipex->end[READ]);
	if (dup2(pipex->fd1, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("DUP IN ERROR", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->end[WRITE], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("DUP OUT ERROR", 2);
		exit(EXIT_FAILURE);
	}
	close(pipex->fd1);
	if (execve(cmd_path, cmd_args, pipex->envp))
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	child_middle(t_pipex *pipex, int cmd_position)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = pipex->cmd[cmd_position]->cmd_path;
	cmd_args = pipex->cmd[cmd_position]->cmd_args;
	if (dup2(pipex->end[READ], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("DUP IN ERROR\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->end[WRITE], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("DUP OUT ERROR\n", 2);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_path, cmd_args, pipex->envp))
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	child_last(t_pipex *pipex, int cmd_position)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = pipex->cmd[cmd_position]->cmd_path;
	cmd_args = pipex->cmd[cmd_position]->cmd_args;
	close(pipex->end[WRITE]);
	if (dup2(pipex->end[READ], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("DUP IN ERROR", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->fd2, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("DUP OUT ERROR", 2);
		exit(EXIT_FAILURE);
	}
	close(pipex->fd2);
	if (execve(cmd_path, cmd_args, pipex->envp))
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
// errno
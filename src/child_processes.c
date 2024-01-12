/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:11:02 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/12 17:53:22 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <stdio.h>

//	0		1			2				3			4				5
// ./pipex infile 		cmd1 		cmd2 	outfile
// ./pipex here_doc  LIMITER cmd1 	cmd2 		outfile

void	manage_child(t_pipex *pipex, int cmd_position, int pipe_position)
{
	// if (pipex->cmd[cmd_position]->cmd_path == NULL)
	// {
	// 	free_finish(pipex);
	// 	exit(EXIT_FAILURE);
	// }
	if (cmd_position == 0 && !pipex->has_herodoc)
		child_first(pipex, cmd_position, pipe_position);
	else if (cmd_position < pipex->cmd_quantity - 1)
		child_middle(pipex, cmd_position, pipe_position);
	else
		child_last(pipex, cmd_position, pipe_position);
}

void	here_doc(t_pipex *pipex, int cmd_position, int pipe_position)
{
	char	*line;
	char	*limiter;
	int		i;

	i = 0;
	if (pipex->cmd[cmd_position]->cmd_path == NULL)
	{
		free_finish(pipex);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(1);
	close(pipex->tube[pipe_position].read_end);
	if (line == NULL)
		exit(EXIT_FAILURE);
	limiter = pipex->argv[2];
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			get_next_line(-1);
			free_finish(pipex);
			exit(EXIT_SUCCESS);
		}
		write(pipex->tube[pipe_position].write_end, line, ft_strlen(line));
		free(line);
		line = get_next_line(1);
	}
	get_next_line(-1);
	free_finish(pipex);
	exit(EXIT_FAILURE);
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

void	child_middle(t_pipex *pipex, int cmd_position, int pipe_position)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = pipex->cmd[cmd_position]->cmd_path;
	cmd_args = pipex->cmd[cmd_position]->cmd_args;
	if (dup2(pipex->tube[pipe_position - 1].read_end, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipex->tube[pipe_position].write_end, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	// close(pipex->fd1);
	// close(pipex->fd2);
	close_pipes(pipex);
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
	// close_pipes(pipex);
	// ft_putstr_fd("----------------------\n", 2);
	// ft_putnbr_fd(execve(cmd_path, cmd_args, pipex->envp), 2);
	// ft_putstr_fd("----------------------\n", 2);
	execve(cmd_path, cmd_args, pipex->envp);
	free_finish(pipex);
	exit(EXIT_FAILURE);
}
// errno

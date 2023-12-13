/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:11:02 by leduard2          #+#    #+#             */
/*   Updated: 2023/12/13 17:19:29 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <stdio.h>

//	0		1		 2	  	 3	    4		 	5
// ./pipex infile 	 cmd1 	 cmd2 	outfile
// ./pipex here_doc  LIMITER cmd1 	cmd2 		outfile
void	here_doc(t_pipex *pipex, int cmd_position)
{
	char	*line;
	char	*limiter;
	int		i;

	i = 0;
	line = get_next_line(1);
	if (line == NULL)
		exit(EXIT_FAILURE);
	limiter = pipex->argv[2];
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			exit(EXIT_SUCCESS);
		write(pipex->tube[0].write_end, &line, ft_strlen(line));
		line = get_next_line(1);
	}
	exit(EXIT_SUCCESS);
}

void	manage_child(t_pipex *pipex, int cmd_position)
{
	if (pipex->argv[1] != "here_doc")
	
		child_first(pipex, cmd_position);
	if (cmd_position == 0)
	{
	}
	else if (cmd_position < pipex->cmd_quantity - 1)
		child_middle(pipex, cmd_position);
	else
		child_last(pipex, cmd_position);
}

void	child_limiter(t_pipex *pipex, int cmd_position)
{
	char	*cmd_path;
	char	**cmd_args;

	ft_putnbr_fd(cmd_position, 2);
	ft_putstr_fd(": child first limiter\n", 2);
	cmd_path = pipex->cmd[cmd_position]->cmd_path;
	cmd_args = pipex->cmd[cmd_position]->cmd_args;
	close(pipex->tube[cmd_position].read_end);
	if (dup2(pipex->fd1, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("DUP IN ERROR", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->tube[cmd_position].write_end, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("DUP OUT ERROR", 2);
		exit(EXIT_FAILURE);
	}
	close(pipex->fd1);
	close(pipex->fd2);
	close_pipes(pipex);
	if (execve(cmd_path, cmd_args, pipex->envp))
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	child_first(t_pipex *pipex, int cmd_position)
{
	char	*cmd_path;
	char	**cmd_args;

	ft_putnbr_fd(cmd_position, 2);
	ft_putstr_fd(": child first\n", 2);
	cmd_path = pipex->cmd[cmd_position]->cmd_path;
	cmd_args = pipex->cmd[cmd_position]->cmd_args;
	close(pipex->tube[cmd_position].read_end);
	if (dup2(pipex->fd1, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("DUP IN ERROR", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->tube[cmd_position].write_end, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("DUP OUT ERROR", 2);
		exit(EXIT_FAILURE);
	}
	close(pipex->fd1);
	close(pipex->fd2);
	close_pipes(pipex);
	if (execve(cmd_path, cmd_args, pipex->envp))
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	child_middle(t_pipex *pipex, int cmd_position)
{
	char	*cmd_path;
	char	**cmd_args;

	ft_putnbr_fd(cmd_position, 2);
	ft_putstr_fd(": child middle\n", 2);
	cmd_path = pipex->cmd[cmd_position]->cmd_path;
	cmd_args = pipex->cmd[cmd_position]->cmd_args;
	if (dup2(pipex->tube[cmd_position - 1].read_end, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("DUP IN ERROR\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->tube[cmd_position].write_end, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("DUP OUT ERROR\n", 2);
		exit(EXIT_FAILURE);
	}
	close(pipex->fd1);
	close(pipex->fd2);
	close_pipes(pipex);
	if (execve(cmd_path, cmd_args, pipex->envp))
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	child_last(t_pipex *pipex, int cmd_position)
{
	char	*cmd_path;
	char	**cmd_args;

	ft_putnbr_fd(cmd_position, 2);
	ft_putstr_fd(": child last\n", 2);
	cmd_path = pipex->cmd[cmd_position]->cmd_path;
	cmd_args = pipex->cmd[cmd_position]->cmd_args;
	close(pipex->tube[cmd_position].write_end);
	if (dup2(pipex->tube[cmd_position - 1].read_end, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("DUP IN ERROR", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->fd2, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("DUP OUT ERROR", 2);
		exit(EXIT_FAILURE);
	}
	close(pipex->fd1);
	close(pipex->fd2);
	close_pipes(pipex);
	if (execve(cmd_path, cmd_args, pipex->envp))
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
// errno

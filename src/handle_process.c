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

void	child_one(t_pipex *pipex)
{
	char	*first_cmd;
	int		fd;
	int		i;
	char	*cmd_path;
	char	**cmd_args;

	i = -1;
	first_cmd = pipex->cmd[0];
	fd = open(pipex->infile_path, O_RDONLY);
	close(pipex->end[READ]);
	if (fd < 0)
	{
		perror(pipex->infile_path);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("DUP IN ERROR");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->end[WRITE], STDOUT_FILENO) == -1)
	{
		perror("DUP OUT ERROR");
		exit(EXIT_FAILURE);
	}
	close(fd);
	while (pipex->paths[++i] != NULL)
	{
		cmd_args = ft_split(pipex->cmd[0], ' ');
		cmd_path = ft_strjoin(pipex->paths[i], cmd_args[0]);
		execve(cmd_path, cmd_args, pipex->envp);
	}
	ft_putstr_fd(first_cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(EXIT_FAILURE);
}

void	child_two(t_pipex *pipex)
{
	int		i;
	int		fd;
	char	*cmd_path;
	char	**cmd_args;
	char	*second_command;

	i = -1;
	second_command = pipex->cmd[1];
	fd = open(pipex->outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
	
	close(pipex->end[WRITE]);
	if (fd < 0)
	{
		perror("caiu aqui e ");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->end[READ], STDIN_FILENO) == -1)
	{
		perror("DUP OUT ERROR");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("DUP OUT ERROR");
		exit(EXIT_FAILURE);
	}
	close(fd);
	while (pipex->paths[++i] != NULL)
	{
		cmd_args = ft_split(second_command, ' ');
		cmd_path = ft_strjoin(pipex->paths[i], cmd_args[0]);
		execve(cmd_path, cmd_args, pipex->envp);
	}
	ft_putstr_fd(second_command, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(EXIT_FAILURE);
}
//errno

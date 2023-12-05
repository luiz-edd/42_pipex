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

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

t_pipex	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	pipex->infile_path = argv[1];
	pipex->outfile_path = argv[argc - 1];
	pipex->cmd = (char **)malloc(sizeof(char *) * (argc - 3));
	while (i < argc - 3)
	{
		pipex->cmd[i] = argv[i + 2];
		i++;
	}
	pipex->argv = argv;
	pipex->envp = envp;
	return (pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;
	int		child_pid;
	int		status;

	child_pid = 0;
	i = 0;
	// if (argv < 5)
	// 	return (2);
	pipex = init_pipex(argc, argv, envp);
	if (pipe(pipex->end) == -1)
		perror("PIPE ERROR");
	if (!format_str(pipex))
		return (2);
	pipex->pid = fork();
	if (pipex->pid == 0)
		child_one(pipex);
	else
	{
		waitpid(pipex->pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (2);
	}
	pipex->pid = fork();
	if (pipex->pid == 0)
		child_two(pipex);
	else
	{
		waitpid(pipex->pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (2);
	}
	// if (pipex->pid != 0)
	// 	wait(NULL);
}

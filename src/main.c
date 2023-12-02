/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:58:02 by leduard2          #+#    #+#             */
/*   Updated: 2023/12/02 14:59:35 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	test(void)
{
	char	**pp;
}

t_pipex	*init_pipex(int argc, char **argv)
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
	pipex->pid = fork();
	pipex->argv = argv;
	return (pipex);
}

static void	manage_child(t_pipex *pipex)
{
	char	*first_cmd;
	int		fd;
	char *args[] = {"cat", "test2", NULL};

	first_cmd = pipex->cmd[0];
	fd = open(pipex->infile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
	dup2(fd,STDOUT_FILENO);
	close(fd);
	
	if(execvp(first_cmd,args) == -1)
	{
		ft_printf("ERROR\n");
	}
}

static void	manage_pid(t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		manage_child(pipex);
	}
}

// ./pipex infile cmd1 cmd2 ... outfile
int	main(int argc, char **argv, char **envp)
{
	t_pipex *pipex;
	if (argc < 5)
		return (2);
	pipex = init_pipex(argc, argv);
	if (pipex->pid == 0)
		manage_pid(pipex);
}
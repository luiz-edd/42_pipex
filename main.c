/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:58:02 by leduard2          #+#    #+#             */
/*   Updated: 2023/11/29 18:19:04 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void test(void)
{
	char **pp;

	
}

t_pipex *init_pipex(int argc, char **argv)
{
	t_pipex	*pipex;
	int		i;

	i = 3;
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	
	pipex->infile_path = argv[1];
	pipex->outfile_path = argv[argc - 1];
	pipex->cmd = ft_lstnew(argv[2]);
	
	while (i < argc - 1)
	{
		ft_lstadd_back(pipex->cmd, ft_lstnew(argv[i]));
		i++;
	}
	pipex->pid = fork();
	return pipex;
}

static void manage_child(t_pipex *pipex)
{
	
}

static void manage_pid(t_pipex *pipex)
{
	pipex->pid = fork();
	if(pipex->pid == 0)
	{
		manage_child(pipex)
	}
}

// ./pipex infile cmd1 cmd2 ... outfile
int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	if (argc < 5)
		return (2);
	pipex = init_pipex(argc, argv);
	if(pipex->pid == 0)
		manage_pid(pipex);
}
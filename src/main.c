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

int	open_files(t_pipex *pipex)
{
	pipex->fd1 = open(pipex->infile_path, O_RDONLY);
	pipex->fd2 = open(pipex->outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd1 < 0)
	{
		perror(pipex->infile_path);
		return (0);
	}
	if (pipex->fd2 < 0)
	{
		perror(pipex->outfile_path);
		return (0);
	}
	return (1);
}

t_pipex	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->infile_path = argv[1];
	pipex->outfile_path = argv[argc - 1];
	if (!open_files(pipex))
	{
		free(pipex);
		return (NULL);
	}
	pipex->cmd = (t_cmd **)malloc(sizeof(t_cmd *) * (argc - 3));
	pipex->cmd_quantity = argc - 3;
	format_str(pipex);


	while (verify_cmd(pipex, i))
		return (pipex);
}
// entrada -> mallocar pipex -> popular pipex -> verificar fd1 ->
// verificar fd2 -> verificar comandos do primeiro ao ultimo -> 
// popular pipex com comandos verificados
// fork() 1 executar primeiro comando -> se a flag falhar, parar tudo
// fork() n* executar n* comandos -> se a flag falhar, parar tudo
// fork() 3 executar ultimo comando -> se a flag falhar, parar tudo

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;
	int		status;
	int		status2;

	i = 0;
	if (argv < 5)
		return (2);
	pipex = init_pipex(argc, argv, envp);
	if (!pipex || !format_str(pipex) || !verify_cmd(pipex))
		return (2);
	if (pipe(pipex->end) == -1)
		ft_printf("PIPE ERROR");
	while (i < pipex->n_cmd)
	{
		pipex->pid = fork();
		if (pipex->pid == 0)
		{
			if (pipex->n_cmd == argc)
				child_first(pipex);
			else if (pipex->n_cmd != 1)
				child_middle(pipex);
			else
				child_last(pipex);
		}
		else
		{
			waitpid(pipex->pid, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
				return (2);
		}
		i++;
	}
	// if (pipex->pid != 0)
	// 	wait(NULL);
}

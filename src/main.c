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

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->cmd_quantity))
	{
		close(pipex->tube[i].read_end);
		close(pipex->tube[i].write_end);
		i++;
	}
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
	pipex = create_pipex(argc, argv, envp);
	if (!pipex)
		return (2);
	while (i < pipex->cmd_quantity)
	{
		pipex->pid = fork();
		if (pipex->pid == 0)
		{
			if (i == 0)
				child_first(pipex, i);
			else if (i < pipex->cmd_quantity - 1)
				child_middle(pipex, i);
			else
				child_last(pipex, i);
		}
		else
		{
			close(pipex->tube[i].write_end);
			waitpid(pipex->pid, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				ft_putstr_fd("command errror\n", 2);
				return (2);
			}
			i++;
		}
		
	}
	// if (pipex->pid != 0)
	// 	wait(NULL);
	// close_pipes(pipex);
}

// // fork 1
// pipex->pid = fork();
// if (pipex->pid == 0)
// 	child_first(pipex, 0);
// // else
// // 	waitpid(pipex->pid, NULL, 0);;
// // fork 2
// pipex->pid = fork();
// if (pipex->pid == 0)
// 	child_middle(pipex, 1);
// else
// 	wait(NULL);
// // fork 3
// pipex->pid = fork();
// if (pipex->pid == 0)
// 	child_last(pipex, 2);
// // else
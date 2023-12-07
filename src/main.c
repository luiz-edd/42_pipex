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
	if (pipe(pipex->end) == -1)
	{
		ft_printf("PIPE ERROR");
		return (2);
	}
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
		// else
		// {
		// 	waitpid(pipex->pid, &status, 0);
		// 	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		// 		return (2);
		// }
		i++;
	}
	if (pipex->pid != 0)
		wait(NULL);
}

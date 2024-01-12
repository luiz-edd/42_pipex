/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:58:02 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/12 12:49:42 by leduard2         ###   ########.fr       */
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
	int j;

	i = 0;
	if(pipex->has_herodoc)
		j = pipex->has_herodoc + 1;
	else
		j = pipex->has_herodoc;
	while (i < j)
	{
		close(pipex->tube[i].read_end);
		close(pipex->tube[i].write_end);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;
	int		j;
	int		status;

	i = 0;
	j = 0;
	if (argv < 5)
	{
		ft_printf("missing args\n");
		return (2);
	}
	pipex = create_pipex(argc, argv, envp);
	if (!pipex)
		return (2);
	while (i < pipex->cmd_quantity)
	{
		pipex->pid = fork();
		if (pipex->pid == 0)
		{
			// ft_printf("----------------------------------------------------\n");
			// ft_printf("cmd_position: %d\npipe_position: %d\n",i, j);
			// ft_print_words(pipex->cmd[i]->cmd_args);
			// ft_printf("----------------------------------------------------\n");
			if (pipex->has_herodoc && j == 0)
				here_doc(pipex, i, j);
			else
			{
				verify_cmd(pipex, i);
				manage_child(pipex, i, j);
			}
		}
		else
		{
			if (!(pipex->has_herodoc && j == 0))
				i++;
			close(pipex->tube[j++].write_end);
			if (i == pipex->cmd_quantity)
				waitpid(pipex->pid, &status, 0);
			else
				wait(NULL);
			// 	ft_printf("nao entrou aqui\n");
			// waitpid(pipex->pid, &status, 0);
			// if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			// 	return (free_finish(pipex));
		}
	}
	free_finish(pipex);
}

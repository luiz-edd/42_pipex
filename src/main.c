/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:58:02 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/08 18:47:53 by leduard2         ###   ########.fr       */
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
		if (verify_cmd(pipex, i) == SUCCESS)
			pipex->pid = fork();
		if (pipex->pid == 0)
		{
			if (pipex->has_herodoc && j == 0)
				here_doc(pipex, i, j);
			else
				manage_child(pipex, i, j);
		}
		else
		{
			if( !(pipex->has_herodoc && j == 0))
				i++;
			close(pipex->tube[j++].write_end);
			waitpid(pipex->pid, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
				return (free_finish(pipex));
		}
	}
	free_finish(pipex);
}

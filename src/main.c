/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:58:02 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/12 17:58:40 by leduard2         ###   ########.fr       */
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
	int	j;

	i = 0;
	if (pipex->has_herodoc)
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
		if (!(pipex->has_herodoc && j == 0))
		{
			if (verify_cmd(pipex, i) == ERROR && i == pipex->cmd_quantity - 1)
				pipex->error_code = 127;
		}
		pipex->pid = fork();
		if (pipex->pid == 0)
		{
			ft_printf("cmd_position: %d\npipe_position: %d\n", i, j);
			ft_print_words(pipex->cmd[i]->cmd_args);
			ft_printf("cmd_name:%s\n", pipex->cmd[i]->cmd_name);
			ft_printf("cmd_path:%s\n", pipex->cmd[i]->cmd_path);
			ft_printf("----------------------------------------------------\n");
			ft_printf("----------------------------------------------------\n");
			if (pipex->has_herodoc && j == 0)
				here_doc(pipex, i, j);
			else
				manage_child(pipex, i, j);
		}
		else
		{
			if (!(pipex->has_herodoc && j == 0))
				i++;
			close(pipex->tube[j++].write_end);
			if (i == pipex->cmd_quantity)
			{
				waitpid(pipex->pid, &status, 0);
				pipex->error_code = (((status)&0xff00) >> 8);
			}
			else
				wait(NULL);
		}
	}
	if (pipex->fd2 < 0)
		pipex->error_code = 1;
	status = pipex->error_code;
	free_finish(pipex);
	ft_printf("error code:%d\n", status);
	return (status);
}

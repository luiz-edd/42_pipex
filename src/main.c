/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:58:02 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/12 19:04:57 by leduard2         ###   ########.fr       */
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

void	ft_manage_father(t_pipex *pipex, int *i, int *j, int *status)
{
	if (!(pipex->has_herodoc && *j == 0))
		if (verify_cmd(pipex, *i) == ERROR && *i == pipex->cmd_quantity - 1)
			pipex->error_code = 127;
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		if (pipex->has_herodoc && *j == 0)
			here_doc(pipex, *i, *j);
		else
			manage_child(pipex, *i, *j);
	}
	else
	{
		if (!(pipex->has_herodoc && *j == 0))
			*i += 1;
		close(pipex->tube[(*j)++].write_end);
		if (*i == pipex->cmd_quantity)
		{
			waitpid(pipex->pid, status, 0);
			if ((((*status) & 0xff00) >> 8) == 1 && pipex->error_code != 127)
				pipex->error_code = 1;
		}
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
	if (argc < 5)
	{
		ft_printf("missing args\n");
		return (2);
	}
	pipex = create_pipex(argc, argv, envp);
	if (!pipex)
		return (2);
	while (i < pipex->cmd_quantity)
		ft_manage_father(pipex, &i, &j, &status);
	status = pipex->error_code;
	if (pipex->fd2 < 0)
		status = 1;
	free_finish(pipex);
	return (status);
}

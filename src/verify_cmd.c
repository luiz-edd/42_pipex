/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:52:10 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/19 20:30:05 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	print_access_error(int code, char *command)
{
	if (command != NULL)
	{
		if (code == R_OK)
			ft_printf("%s: command not readable\n", command);
		else if (code == X_OK)
			ft_printf("%s: command not executable\n", command);
		else if (code == NOT_FOUND)
			ft_printf("%s: command not found\n", command);
	}
	return (ERROR);
}

static int	verify_access(char *cmd)
{
	if (cmd == NULL)
		return (NOT_FOUND);
	if (!access(cmd, F_OK))
	{
		if (access(cmd, R_OK))
			return (R_OK);
		else if (access(cmd, X_OK))
			return (X_OK);
		else
			return (FOUND);
	}
	return (NOT_FOUND);
}

static char	**ft_assign_cmd_args(t_pipex *pipex, int cmd_position)
{
	char	**cmd_args;

	if (pipex->has_herodoc)
		cmd_args = ft_quote_split(pipex->argv[cmd_position + 3], ' ');
	else
		cmd_args = ft_quote_split(pipex->argv[cmd_position + 2], ' ');
	return (cmd_args);
}

static int	ft_assign_cmd_path(t_pipex *pipex, int cmd_position,
		int access_status, int i)
{
	while (pipex->paths[++i] && access_status == NOT_FOUND)
	{
		pipex->cmd[cmd_position]->cmd_path = ft_strjoin(pipex->paths[i],
				pipex->cmd[cmd_position]->cmd_name);
		access_status = verify_access(pipex->cmd[cmd_position]->cmd_path);
		if (access_status != NOT_FOUND)
			break ;
		free(pipex->cmd[cmd_position]->cmd_path);
		pipex->cmd[cmd_position]->cmd_path = NULL;
	}
	if (access_status != FOUND)
	{
		if (pipex->cmd[cmd_position]->cmd_path == NULL)
			pipex->cmd[cmd_position]->cmd_path = ft_strjoin(pipex->paths[i - 1],
					pipex->cmd[cmd_position]->cmd_name);
		print_access_error(access_status, pipex->cmd[cmd_position]->cmd_name);
		return (ERROR);
	}
	return (SUCCESS);
}

int	verify_cmd(t_pipex *pipex, int cmd_position)
{
	int	i;
	int	access_status;

	i = -1;
	pipex->cmd[cmd_position]->cmd_args = ft_assign_cmd_args(pipex,
			cmd_position);
	pipex->cmd[cmd_position]->cmd_name = pipex->cmd[cmd_position]->cmd_args[0];
	access_status = NOT_FOUND;
	return (ft_assign_cmd_path(pipex, cmd_position, access_status, i));
}

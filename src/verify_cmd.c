/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:52:10 by leduard2          #+#    #+#             */
/*   Updated: 2023/12/05 20:14:34 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	verify_access(char *filename)
{
	if (filename == NULL)
		return (ERROR);
	if (!access(filename, F_OK))
	{
		if (access(filename, R_OK))
			return (R_OK);
		else if (access(filename, X_OK))
			return (X_OK);
		else
			return (SUCCESS);
	}
	return (ERROR);
}

int	verify_cmd(t_pipex *pipex, int cmd_position)
{
	int i;
	char *cmd_name;
	char **cmd_args;
	char *cmd_path;

	i = -1;
	cmd_args = pipex->argv[i + 2];
	cmd_name = cmd_args[0];

	while (pipex->paths[++i])
	{
		cmd_path = ft_strjoin(pipex->paths[i], cmd_name);
		if (cmd_path == NULL)
			return (ERROR);
		
	}
}
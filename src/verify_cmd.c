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

static int	print_access_error(int code, char *command)
{
	if (code == R_OK)
		ft_printf("%s: command not readable\n", command);
	else if (code == X_OK)
		ft_printf("%s: command not executable\n", command);
	else if (code == NOT_FOUND)
		ft_printf("%s: command not found\n", command);
	return (ERROR);
}

static int	verify_access(char *filename)
{
	if (filename == NULL)
		return (NOT_FOUND);
	if (!access(filename, F_OK))
	{
		if (access(filename, R_OK))
			return (R_OK);
		else if (access(filename, X_OK))
			return (X_OK);
		else
			return (FOUNDED);
	}
	return (NOT_FOUND);
}

int	verify_cmd(t_pipex *pipex, int cmd_position)
{
	int i;
	int access_status;
	char *cmd_name;
	char **cmd_args;
	char *cmd_path;

	i = -1;
	cmd_args = ft_split(pipex->argv[cmd_position + 2], ' ');
	cmd_name = cmd_args[0];
	access_status = NOT_FOUND;

	while (pipex->paths[++i] && access_status == NOT_FOUND)
	{
		cmd_path = ft_strjoin(pipex->paths[i], cmd_name);
		access_status = verify_access(cmd_path);
	}
	if (access_status != FOUNDED)
		return (print_access_error(access_status, cmd_name));
	
	pipex->cmd[cmd_position]->cmd_args = cmd_args;
	pipex->cmd[cmd_position]->cmd_name = cmd_name;
	pipex->cmd[cmd_position]->cmd_path = cmd_path;
	ft_printf("Path: %s\nName:%s\nArgs: ", pipex->cmd[cmd_position]->cmd_path, pipex->cmd[cmd_position]->cmd_name);
	ft_print_words(pipex->cmd[cmd_position]->cmd_args);
	return (SUCCESS);
}
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
//	0		1			2				3			4			5
// ./pipex infile 		cmd1 		cmd2 	outfile
// ./pipex here_doc  LIMITER cmd1 	cmd2 		outfile
int	verify_cmd(t_pipex *pipex, int cmd_position)
{
	int i;
	int access_status;
	char *cmd_name;
	char **cmd_args;
	char *cmd_path;

	i = -1;
	if (pipex->has_herodoc)
		cmd_args = ft_quote_split(pipex->argv[cmd_position + 3], ' ');
	else
		cmd_args = ft_quote_split(pipex->argv[cmd_position + 2], ' ');

	if (cmd_args == NULL)
		return (ERROR);
	cmd_name = cmd_args[0];
	access_status = NOT_FOUND;

	while (pipex->paths[++i] && access_status == NOT_FOUND)
	{
		cmd_path = ft_strjoin(pipex->paths[i], cmd_name);
		if (cmd_path == NULL)
			return (ERROR);
		access_status = verify_access(cmd_path);
		if (access_status != NOT_FOUND)
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	if (access_status != FOUND)
	{
		if (cmd_path == NULL)
			cmd_path = ft_strjoin(pipex->paths[i - 1], cmd_name);
		print_access_error(access_status, cmd_name);
	}
	pipex->cmd[cmd_position]->cmd_args = cmd_args;
	pipex->cmd[cmd_position]->cmd_name = cmd_name;
	pipex->cmd[cmd_position]->cmd_path = cmd_path;
	if (access_status != FOUND)
		return (ERROR);
	else
		return (SUCCESS);
}
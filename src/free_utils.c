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

#include "pipex.h";

static void	free_cmd_struct(t_cmd **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->cmd_path != NULL)
			free(cmd[i]->cmd_path);
		cmd[i]->cmd_path = NULL;
		j = 0;
		// if (cmd[i]->cmd_args[j] != NULL)
		// {
		// 	while (cmd[i]->cmd_args[j])
		// 	{
		// 		if (cmd[i]->cmd_args[j] != NULL)
		// 		{
		// 			free(cmd[i]->cmd_args[j]);
		// 			cmd[i]->cmd_args[j] = NULL;
		// 		}
		// 		j++;
		// 	}
		// }
		if (cmd[i]->cmd_args != NULL)
		{
			free(cmd[i]->cmd_args);
			cmd[i]->cmd_args = NULL;
		}
		i++;
	}
	free(cmd);
	cmd = NULL;
}

void	*free_pipex(t_pipex *pipex)
{
	if (pipex != NULL)
	{
		if (pipex->cmd != NULL)
			free_cmd_struct(pipex->cmd);
		if (pipex->tube != NULL)
			free(pipex->tube);
		if (pipex != NULL)
			free(pipex);
	}
	return (NULL);
}

void	*free_all(char *str1, char *str2, char *str3)
{
	if (str1 != NULL)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2 != NULL)
	{
		free(str2);
		str2 = NULL;
	}
	if (str3 != NULL)
	{
		free(str3);
		str3 = NULL;
	}
	return (NULL);
}

void	*free_matrix(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
	return (NULL);
}
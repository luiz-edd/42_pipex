/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:11:02 by leduard2          #+#    #+#             */
/*   Updated: 2023/12/05 19:16:25 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_cmd_struct(t_cmd **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->cmd_path != NULL)
			free(cmd[i]->cmd_path);
		if (cmd[i]->cmd_name != NULL)
			free(cmd[i]->cmd_name);
		cmd[i]->cmd_path = NULL;
		cmd[i]->cmd_name = NULL;
		j = 0;
		while (cmd[i]->cmd_args[j])
		{
			free(cmd[i]->cmd_args[j]);
			cmd[i]->cmd_args[j] = NULL;
			j++;
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
		if (pipex != NULL)
			free(pipex);
	}
	return (NULL);
}

static int	open_files(t_pipex *pipex)
{
	pipex->fd1 = open(pipex->infile_path, O_RDONLY);
	pipex->fd2 = open(pipex->outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd1 < 0)
	{
		perror(pipex->infile_path);
		return (ERROR);
	}
	if (pipex->fd2 < 0)
	{
		perror(pipex->outfile_path);
		return (ERROR);
	}
	return (SUCCESS);
}
char	*get_path(t_pipex *pipex)
{
	int		i;
	char	**envp;

	envp = pipex->envp;
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

static int	get_env_path(t_pipex *pipex)
{
	char	*path;
	int		i;

	i = -1;
	path = get_path(pipex);
	if (path == NULL)
	{
		ft_printf("PATH NOT FOUND\n");
		return (ERROR);
	}
	while (*path != '=')
		path++;
	path++;
	pipex->paths = ft_split(path, ':');
	while (pipex->paths[++i])
		pipex->paths[i] = ft_strjoin(pipex->paths[i], "/");
	return (SUCCESS);
}

int	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	pipex = (t_pipex *)ft_calloc(sizeof(t_pipex), 1);
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->infile_path = argv[1];
	pipex->outfile_path = argv[argc - 1];
	pipex->cmd = (t_cmd **)ft_calloc(sizeof(t_cmd *), (argc - 3));
	pipex->cmd_quantity = argc - 3;
	if (open_files(pipex) == ERROR || get_env_path(pipex) == ERROR)
		return (free_pipex(pipex));
	while (i < pipex->cmd_quantity)
	{
		if (verify_cmd(pipex, i) == ERROR)
		{
			free_pipex(pipex);
			return (NULL);
		}
		i++;
	}
	return (pipex);
}

t_pipex	*create_pipex(int argc, char **argv, char **envp)
{
	t_pipex *pipex;
}
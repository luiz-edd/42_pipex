/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:11:02 by leduard2          #+#    #+#             */
/*   Updated: 2024/01/16 15:43:59 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_files(t_pipex *pipex)
{
	pipex->fd1 = -1;
	if (!pipex->has_herodoc)
		pipex->fd1 = open(pipex->infile_path, O_RDONLY);
	if (pipex->fd1 < 0 && !pipex->has_herodoc)
		perror(pipex->infile_path);
	if (pipex->has_herodoc)
		pipex->fd2 = open(pipex->outfile_path, O_WRONLY | O_CREAT | O_APPEND);
	else
		pipex->fd2 = open(pipex->outfile_path, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	if (pipex->fd2 < 0)
		perror(pipex->outfile_path);
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
	ft_printf("PATH NOT FOUND\n");
	return (NULL);
}

static int	create_env_path(t_pipex *pipex)
{
	char	*path;
	char	*aux;
	int		i;

	i = -1;
	path = get_path(pipex);
	if (path != NULL)
		while (*path != '=')
			path++;
	path++;
	pipex->paths = ft_split(path, ':');
	while (pipex->paths[++i])
	{
		aux = pipex->paths[i];
		pipex->paths[i] = ft_strjoin(pipex->paths[i], "/");
		free(aux);
		aux = NULL;
	}
	return (SUCCESS);
}

int	create_tubes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_quantity)
	{
		if (pipe((int *)&pipex->tube[i]) == -1)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

t_pipex	*create_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)ft_calloc(sizeof(t_pipex), 1);
	pipex->argv = argv;
	pipex->cmd_quantity = ft_malloc_tube_and_cmd(pipex, argc);
	pipex->envp = envp;
	pipex->infile_path = argv[1];
	pipex->outfile_path = argv[argc - 1];
	pipex->error_code = 0;
	pipex->pid = 0;
	if (open_files(pipex) == ERROR || create_tubes(pipex) == ERROR
		|| create_env_path(pipex) == ERROR)
		return (free_pipex(pipex->tube, pipex->cmd, pipex));
	return (pipex);
}

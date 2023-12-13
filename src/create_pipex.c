/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:11:02 by leduard2          #+#    #+#             */
/*   Updated: 2023/12/13 15:48:49 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (path == NULL)
		while (*path != '=')
			path++;
	path++;
	pipex->paths = ft_split(path, ':');
	if (pipex->paths == NULL)
		return (ERROR);
	while (pipex->paths[++i])
	{
		aux = pipex->paths[i];
		pipex->paths[i] = ft_strjoin(pipex->paths[i], "/");
		free(aux);
		aux = NULL;
		if (pipex->paths[i] == NULL)
			return (free_matrix(pipex->paths));
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

//	0		1		 2	  	 3	    4		 5
// ./pipex infile 		cmd1 	 cmd2 	outfile
// ./pipex here_doc  LIMITER cmd1 	cmd2 		outfile
t_pipex	*create_pipex(int argc, char **argv, char **envp)
{
	int		i;
	int		j;
	t_pipex	*pipex;
	int		cmd_quantity;

	i = 0;
	j = 0;
	if (argv[1] == "here_doc")
		cmd_quantity = argc - 4;
	else
		cmd_quantity = argc - 3;
	pipex = (t_pipex *)ft_calloc(sizeof(t_pipex), 1);
	pipex->tube = (t_tube *)ft_calloc(sizeof(t_tube *), cmd_quantity);
	pipex->cmd = (t_cmd **)ft_calloc(sizeof(t_cmd **), cmd_quantity);
	while (i < cmd_quantity)
		pipex->cmd[i++] = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	pipex->cmd_quantity = cmd_quantity;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->infile_path = argv[1];
	pipex->outfile_path = argv[argc - 1];
	if (open_files(pipex) == ERROR || create_tubes(pipex) == ERROR
		|| create_env_path(pipex) == ERROR)
		return (free_pipex(pipex->tube, pipex->cmd, pipex));
	i = 0;
	while (i < cmd_quantity)
	{
		if (verify_cmd(pipex, i) == ERROR)
		{
			j = 0;
			while (j < i)
			{
				free(pipex->cmd[j]->cmd_path);
				free_matrix(pipex->cmd[j]->cmd_args);
				j++;
			}
			close(pipex->fd1);
			close(pipex->fd2);
			free_matrix(pipex->paths);
			return (free_pipex(pipex->tube, pipex->cmd, pipex));
		}
		i++;
	}
	return (pipex);
}

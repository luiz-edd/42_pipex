/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:58:02 by leduard2          #+#    #+#             */
/*   Updated: 2023/12/04 18:57:27 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

t_pipex	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	pipex->infile_path = argv[1];
	pipex->outfile_path = argv[argc - 1];
	pipex->cmd = (char **)malloc(sizeof(char *) * (argc - 3));
	while (i < argc - 3)
	{
		pipex->cmd[i] = argv[i + 2];
		i++;
	}
	pipex->argv = argv;
	pipex->envp = envp;
	return (pipex);
}

// int execve(const char *path, char *const argv[], char *envp[]);
static void	child_process(t_pipex *pipex)
{
	char	*first_cmd;
	int		fd;
	int		fd2;
	int		i;
	char	*cmd_path;
	char	**cmd_args;
	
	i = -1;
	first_cmd = pipex->cmd[0];
	fd = open(pipex->infile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fd2 = open(pipex->outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(pipex->end[READ]);
	if (fd < 0)
	{
		perror("FILE NOT FOUND");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("DUP IN ERROR");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
	{
		perror("DUP OUT ERROR");
		exit(EXIT_FAILURE);
	}
	close(fd);
	while (pipex->paths[++i] != NULL)
	{
		cmd_args = ft_split(pipex->cmd[0], ' ');
		cmd_path = ft_strjoin(pipex->paths[i], cmd_args[0]);
		ft_print_words(cmd_args);
		execve(cmd_path, cmd_args, pipex->envp);
	}
	perror("COMMAND NOT FOUND");
	// exit(EXIT_SUCCESS);
}

// ./pipex infile cmd1 cmd2 ... outfile
int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;
	int		child_pid;

	child_pid = 0;
	if (!argv)
		return (2);
	pipex = init_pipex(argc, argv, envp);
	if (pipe(pipex->end) == -1)
		perror("PIPE ERROR");
	if (!format_str(pipex))
		return (2);
	pipex->pid = fork();
	i = 0;
	if (pipex->pid == 0)
	{
		ft_printf("infile_path: %s\noutfile_path: %s\n",pipex->infile_path,pipex->outfile_path);
		child_pid = getpid();
		child_process(pipex);
		
	}
	
	if (pipex->pid != 0)
		wait(NULL);
	
	
}

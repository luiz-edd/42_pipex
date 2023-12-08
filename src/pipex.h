/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:20:50 by leduard2          #+#    #+#             */
/*   Updated: 2023/12/05 15:25:11 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/src/libft.h"
# include <sys/types.h>

# define WRITE 1
# define READ 0
# define ERROR 0
# define SUCCESS 1
# define NOT_FOUND 6
# define FOUNDED 5

typedef struct s_tube
{
	int		read_end;
	int		write_end;
}			t_tube;

typedef struct s_cmd
{
	char	*cmd_path;
	char	**cmd_args;
	char	*cmd_name;
}			t_cmd;

typedef struct s_pipex
{
	char	**argv;
	char	**envp;
	char	**paths;
	int		cmd_quantity;
	char	*infile_path;
	char	*outfile_path;
	int		fd1;
	int		fd2;
	pid_t	pid;
	t_cmd	**cmd;
	t_tube	*tube;
}			t_pipex;

// create_pipex
t_pipex		*create_pipex(int argc, char **argv, char **envp);
void		*free_pipex(t_pipex *pipex);

// child_processes
void		child_first(t_pipex *pipex, int cmd_position);
void		child_middle(t_pipex *pipex, int cmd_position);
void		child_last(t_pipex *pipex, int cmd_position);

// verify_cmd
int			verify_cmd(t_pipex *pipex, int cmd_position);

// main
void		close_pipes(t_pipex *pipex);

#endif
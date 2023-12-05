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

typedef struct s_pipex
{
	char	**cmd;
	char	**paths;
	int		fd1;
	int		fd2;
	int		end[2];
	char	*infile_path;
	char	*outfile_path;
	char	**argv;
	char	**envp;
	pid_t	pid;

}			t_pipex;

//format_str
int			format_str(t_pipex *pipex);

//handle_process
void	child_one(t_pipex *pipex);
void	child_two(t_pipex *pipex);


#endif
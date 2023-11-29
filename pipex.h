/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:20:50 by leduard2          #+#    #+#             */
/*   Updated: 2023/11/29 18:22:08 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "libft/src/libft.h"
# include <sys/types.h>

typedef struct s_pipex
{
	t_list	*cmd;
	int		fd1;
	int		fd2;
	int		end[2];
	char	*infile_path;
	char	*outfile_path;
	pid_t	pid;

}			t_pipex;

#endif
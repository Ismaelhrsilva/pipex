/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:25:14 by ishenriq          #+#    #+#             */
/*   Updated: 2024/02/29 19:50:39 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>      // open, close
# include <unistd.h>     // read, write, close, dup, dup2, execve, fork, pipe, unlink, wait, waitpid
# include <stdlib.h>     // malloc, free, exit
# include <stdio.h>      // perror
# include <errno.h>      // perror, strerror
# include <string.h>     // strerror
# include <unistd.h>     // access
# include <sys/wait.h>

# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"
# include "../lib/libft/gnl/get_next_line.h"

typedef enum 
{
	NODE_CMD = 0,
	NODE_PIPE
}	nodetype;

typedef struct s_node
{
	nodetype type;
	int	t;
	char **args;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct	s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	int		pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		infile;
	int		outfile;
	t_node	*cmd1;
	t_node	*cmd2;
	t_node	*pipenode;
}	t_pipex;

#endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:25:14 by ishenriq          #+#    #+#             */
/*   Updated: 2024/02/25 16:07:48 by ishenriq         ###   ########.fr       */
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
	NODE_CMD;
	NODE_PIPE;
}	nodetype;

typedef struct s_node
{
	nodetype type;
	char **args;
	struct t_node	*left;
	struct t_node	*right;
}	t_node;

/*typedef struct	s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
}	t_pipex;
*/



#endif


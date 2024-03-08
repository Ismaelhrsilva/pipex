/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:25:14 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/08 12:01:01 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>      // open, close
# include <unistd.h>     // read, close, dup2, execve, fork, pipe, waitpid
# include <stdlib.h>     // malloc, free, exit
# include <stdio.h>      // perror
# include <errno.h>      // perror, strerror
# include <string.h>     // strerror
# include <unistd.h>     // access
# include <sys/wait.h>

# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"
# include "../lib/libft/gnl/get_next_line.h"

typedef enum e_nodetype
{
	NODE_CMD = 0,
	NODE_PIPE
}	t_nodetype;

typedef struct s_node
{
	t_nodetype		type;
	int				t;
	char			**args;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*path;
	char	*filename[2];
	int		type_filename[2];
	char	**cmd1_argv;
	char	**cmd2_argv;
	int		pipe_fd[2];
	pid_t	pid_left;
	int		infile;
	int		outfile;
	t_node	*cmd1;
	t_node	*cmd2;
	t_node	*pipenode;
	int		status;
	char	**split;
}	t_pipex;

t_node	*create_cmd_node(char **args, int t);
t_node	*create_pipe_node(t_pipex *pipex);
void	free_ast(t_node *root);
void	*init_pipex(void);
void	left_child(t_pipex *pipex);
void	right_child(t_pipex *pipex);
void	ft_error(t_pipex *pipex, char *exec, char *message, int status);
void	get_cmd(t_pipex *pipex);
void	ft_envp(t_pipex *pipex, char *exec, int cmd);
void	get_filename(t_pipex *pipex, char **split, char *exec, int cmd);
void	erase(t_pipex *pipex);
void	close_and_end(t_pipex *pipex);
#endif

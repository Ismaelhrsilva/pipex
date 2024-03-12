/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:25:14 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/12 17:43:20 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

#define HEREDOC "here_doc"
#define TEMP "/temp/heredoc"

enum e_pipe
{
	READ,
	WRITE
};

enum e_signal
{
	INFILE,
	OUTFILE,
	MIDFILE
};

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*path;
	int		flag;

	int		type_filename;
	char	*filename;

	int		ncmd;
	char	**cmd_argv;
	
	int		**fds;
	int		infile;
	int		outfile;
	char	*inf;
	char	*outf;

	pid_t	pid;
	int		status;

}	t_pipex;

void	*init_pipex(void);
void	child(t_pipex *pipex, int typefile);
void	open_file(t_pipex *pipex, int typefile);
void	open_dup(t_pipex *pipex, int typefile);
void	ft_execute(t_pipex *pipex, int cmd);
void	ft_error(t_pipex *pipex, char *exec, char *message, int status);
void	get_cmd(t_pipex *pipex);
void	ft_envp(t_pipex *pipex, char *exec);
void	get_filename(t_pipex *pipex, char **split, char *exec);
void	erase(t_pipex *pipex);
void	close_and_end(t_pipex *pipex);
void	ft_pipex(t_pipex *pipex);
void	ft_exit(t_pipex *pipex);
void	construct_fds(t_pipex *pipex);
void	close_fds(int fds[]);
char	*ft_heredoc(t_pipex *pipex);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/10 17:39:30 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/pipex_bonus.h"


void	open_file(t_pipex *pipex, int typefile)
{
	if (typefile == INFILE)
	{
		pipex->infile = open(pipex->inf, O_RDONLY, 0644);
		if (pipex->infile < 0)
		{
			close_fds(pipex->fds[pipex->ncmd - 2]);
			ft_error(pipex, pipex->inf, strerror(errno), 1);
		}
	}
	else if (typefile == MIDFILE)
	{
		return ;
	}
	else
	{
		pipex->outfile = open(pipex->outf, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (pipex->outfile < 0)
		{
			close_fds(pipex->fds[pipex->ncmd - 2]);
			close_fds(pipex->fds[pipex->ncmd - 3]);
			ft_error(pipex, pipex->outf, strerror(errno), 1);
		}
	}
}

void	ft_execute(t_pipex *pipex, int cmd)
{
	int	fd;

	if (pipex->cmd_argv[0])
	{
		fd = open(pipex->cmd_argv[0], O_DIRECTORY | O_RDONLY, 0644);
		if (fd != -1)
		{
			close(fd);
			if (pipex->cmd_argv[0] && ft_strchr(pipex->cmd_argv[0], '/'))
				ft_error(pipex, pipex->cmd_argv[0], "Is a directory", 126);
			ft_error(pipex, pipex->cmd_argv[0], "command not found", 127);
		}
	}
	if (pipex->filename && access(pipex->filename, F_OK | X_OK) == 0 \
	&& execve(pipex->filename, pipex->cmd_argv, pipex->envp) < 0)
		ft_error(pipex, pipex->argv[cmd], strerror(errno), 127);
	if (pipex->cmd_argv[0] && access(pipex->cmd_argv[0], F_OK) == 0)
		if (execve(pipex->cmd_argv[0], pipex->cmd_argv, pipex->envp) < 0)
			ft_error(pipex, pipex->argv[cmd], strerror(errno), 126);
	if (pipex->cmd_argv[0] && pipex->cmd_argv[0][0] == '/')
		ft_error(pipex, pipex->cmd_argv[0],
			"No such file or directory", 127);
	ft_error(pipex, pipex->argv[cmd], "command not found", 127);
}

void	open_dup(t_pipex *pipex, int typefile)
{
	if (typefile == INFILE)
	{
		open_file(pipex, typefile);
		if (dup2(pipex->fds[pipex->ncmd - 2][WRITE], STDOUT_FILENO) == -1)
			ft_error(pipex, "dup2", strerror(errno), 1);
		close(pipex->fds[pipex->ncmd - 2][WRITE]);
		close(pipex->fds[pipex->ncmd - 2][READ]);
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			ft_error(pipex, "dup2", strerror(errno), 1);
		close(pipex->infile);
	}
	else if (typefile == OUTFILE)
	{
		open_file(pipex, typefile);
		if (dup2(pipex->fds[pipex->ncmd - 3][READ], STDIN_FILENO) == -1)
			ft_error(pipex, "dup2", strerror(errno), 1);
		close(pipex->fds[pipex->ncmd - 3][WRITE]);
		close(pipex->fds[pipex->ncmd - 3][READ]);
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			ft_error(pipex, "dup2", strerror(errno), 1);
		close(pipex->outfile);
	}
	else if (typefile == MIDFILE)
	{
		open_file(pipex, typefile);
		if (dup2(pipex->fds[pipex->ncmd - 3][READ], STDIN_FILENO) == -1)
			ft_error(pipex, "dup2", strerror(errno), 1);
		close(pipex->fds[pipex->ncmd - 3][READ]);
		if (dup2(pipex->fds[pipex->ncmd - 2][WRITE], STDOUT_FILENO) == -1)
			ft_error(pipex, "dup2", strerror(errno), 1);
		close(pipex->fds[pipex->ncmd - 2][WRITE]);
	}
}

void	child(t_pipex *pipex, int typefile)
{
	open_dup(pipex, typefile);
	get_cmd(pipex);
	ft_envp(pipex, pipex->cmd_argv[0]);
	ft_execute(pipex, pipex->ncmd);
}

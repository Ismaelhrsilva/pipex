/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/10 11:22:10 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/pipex_bonus.h"


void	child(t_pipex *pipex, int typefile)
{
	open_file(pipex, pipex->typefile);
	ft_envp(pipex, pipex->cmd_argv[pipex->ncmd + 2]);
	get_cmd(pipex);
	ft_execute_node(pipex, pipex->ncmd + 2);
}

void	open_dup(t_pipex *pipex)
{
	if (pipex->typefile == INFILE)
	{
		open_file(pipex, pipex->typefile);
		if (dup2(pipex->pipe_fd[PIPE_IN], STDOUT_FILENO) == -1)
			ft_error(pipex, "dup2", strerror(errno), 1);
		close(pipex->pipe_fd[PIPE_IN]]);
		if (dup2(pipex->fds[x], STDIN_FILENO) == -1)
			ft_error(pipex, "dup2", strerror(errno), 1);
		close(pipex->fds[x]);
	}
	else if (pipex->typefile == OUTFILE)
	{
		open_file(pipex, pipex->typefile);
		if (dup2(pipex->fds[PIPE_OUT], STDIN_FILENO) == -1)
			ft_error(pipex, "dup2", strerror(errno), 1);
		close(pipex->fds[PIPE_OUT]);
		if (dup2(pipex->fds[x], STDOUT_FILENO) == -1)
			ft_error(pipex, "dup2", strerror(errno), 1);
		close(pipex->fds[x]);
	}
	else
	{
		open_file(pipex, pipex->typefile);
		if (dup2(pipex->fds[PIPE_OUT], STDIN_FILENO) == -1)
			ft_error(pipex, "dup2", strerror(errno), 1);
		close(pipex->fds[PIPE_OUT]);
		if (dup2(pipex->fds[x][PIPE_IN], STDOUT_FILENO) == -1)
			ft_error(pipex, "dup2", strerror(errno), 1);
		close(pipex->fds[x]);
	}
}

void	open_file(t_pipex *pipex, int typefile)
{
	if (typefile == INFILE)
	{
		pipex->fds[x] = open(pipex->infile, O_RDONLY, 0644);
		if (pipex->fds[x] < 0)
		{
			close(pipex->pipe_fd[x][0]);
			ft_error(pipex, pipex->infile, strerror(errno), 1);
		}
	}
	else if (typefile == MIDFILE)
	{
		return ;
	}
	else
	{
		pipex->fds[x] = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (pipex->fds[x] < 0)
		{
			//close_fds
			ft_error(pipex, pipex->infile, strerror(errno), 1);
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

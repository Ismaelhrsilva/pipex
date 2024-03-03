/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/03 20:09:41 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

void	left_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	pipex->infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipex->pipe_fd[1]);
}

void	right_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[1]);
	pipex->outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (pipex->outfile == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipex->pipe_fd[0]);
}

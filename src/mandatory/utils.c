/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/08 11:53:43 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

void	*init_pipex(void)
{
	static t_pipex	pipex;

	return (&pipex);
}

void	ft_error(t_pipex *pipex, char *exec, char *message, int status)
{
	char	*join;
	char	*join_1;

	if (!pipex)
		return ;
	join_1 = ft_strjoin(exec, ": ");
	join = ft_strjoin(join_1, message);
	ft_putendl_fd(join, 2);
	free(join);
	free(join_1);
	if (status == EACCES)
		status = 126;
	else if (status == ENOENT)
		status = 127;
	close_and_end(pipex);
	exit(status);
}

void	close_and_end(t_pipex *pipex)
{
	if (pipex->pipenode)
	{
		if (!pipex->filename[0])
			free(pipex->filename[0]);
		if (!pipex->filename[1])
			free(pipex->filename[1]);
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		erase(pipex);
		free_ast(pipex->pipenode);
	}
}

void	erase(t_pipex *pipex)
{
	int	i;

	i = 0;
	// if (pipex->split)
	// {
	// 	while (pipex->split[i] != NULL)
	// 	{
	// 		free(pipex->split[i]);
	// 		i++;
	// 	}
	// 	free(pipex->split);
	// }
	i = 0;
	while (pipex->cmd1_argv[i] != NULL)
	{
		free(pipex->cmd1_argv[i]);
		i++;
	}
	if (pipex->cmd1_argv)
		free(pipex->cmd1_argv);
	i = 0;
	while (pipex->cmd2_argv[i] != NULL)
	{
		free(pipex->cmd2_argv[i]);
		i++;
	}
	if (pipex->cmd2_argv)
		free(pipex->cmd2_argv);
	//free(pipex->cmd1_argv[1]);
	//free(pipex->cmd1_argv);
	//free(pipex->cmd2_argv[1]);
	//free(pipex->cmd2_argv);
}

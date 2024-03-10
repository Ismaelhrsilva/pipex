/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/10 13:02:01 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/pipex_bonus.h"

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
	if (!pipex->type_filename && pipex->filename)
		free(pipex->filename);
	close_fds(pipex->fds[pipex->ncmd]);
	erase(pipex);
}

void	erase(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_argv[i] != NULL)
	{
		free(pipex->cmd_argv[i]);
		i++;
	}
	if (pipex->cmd_argv)
		free(pipex->cmd_argv);
	i = 0;
}

void	ft_exit(t_pipex *pipex)
{
	close_and_end(pipex);
	waitpid(pipex->pid, &pipex->status, 0);
	if (WIFEXITED(pipex->status))
		exit(WEXITSTATUS(pipex->status));
	exit(pipex->status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/01 15:01:34 by ishenriq         ###   ########.fr       */
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
	if (status != 1)
		erase(pipex);
	turnoff_fds();
	kill_fds(pipex);
	exit(status);
}

void	close_and_end(t_pipex *pipex)
{
	if (!pipex->type_filename && pipex->filename)
		free(pipex->filename);
}

void	erase(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (1)
	{
		if (pipex->cmd_argv[i])
			free(pipex->cmd_argv[i]);
		else
			break ;
		i++;
	}
	if (pipex->cmd_argv)
		free(pipex->cmd_argv);
}

void	ft_exit(t_pipex *pipex)
{
	close_and_end(pipex);
	turnoff_fds();
	kill_fds(pipex);
	waitpid(pipex->pid, &pipex->status, WUNTRACED);
	if (WIFEXITED(pipex->status))
		exit(WEXITSTATUS(pipex->status));
	exit(pipex->status);
}

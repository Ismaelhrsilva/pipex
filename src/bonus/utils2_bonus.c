/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/01 14:35:50 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/pipex_bonus.h"

void	construct_fds(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex -> fds = (int **) ft_calloc(pipex->argc, sizeof(int **));
	if (!(pipex->fds))
		ft_error(pipex, "fds", "Failed to allocate memory", 1);
	while (i < pipex->argc - 1)
	{
		pipex->fds[i] = (int *) ft_calloc(2, sizeof(int));
		if (!(pipex->fds[i++]))
			ft_error(pipex, "fd", "Failed to allocate memory", 1);
	}
}

void	close_fds(int fds[])
{
	if (!fds)
		return ;
	close(fds[WRITE]);
	close(fds[READ]);
}

void	turnoff_fds(void)
{
	close(0);
	close(1);
	close(2);
}

void	kill_fds(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (1)
	{
		if (pipex->fds[i])
			free(pipex->fds[i]);
		else
			break ;
		i++;
	}
	if (pipex->fds)
		free(pipex->fds);
}


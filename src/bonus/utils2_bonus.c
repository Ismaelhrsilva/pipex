/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/10 12:44:45 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/pipex_bonus.h"

void	construct_fds(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex -> fds = ft_calloc(data -> argc, sizeof(int **));
	if (!(data -> fds))
		ft_error(pipex, "fds", "Failed to allocate memory", 1);
	while (i < pipex -> argc - 1)
	{
		pipex -> fds[i] = ft_calloc(2, sizeof(int));
		if (!(pipex -> fds[i++]))
			ft_error(pipex, "fd", "Failed to allocate memory", 1);
	}
}

void	close_fds(int fds[])
{
	if (!fds)
		return ;
	close(fds[WRITE]);
	close(fds[READ]);
	fds = 0;
}

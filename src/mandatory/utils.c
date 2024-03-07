/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/06 22:10:09 by ishenriq         ###   ########.fr       */
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

	join_1 = ft_strjoin(exec, ": ");
	join = ft_strjoin(join_1, message);
	ft_putendl_fd(join, 2);
	free(join);
	free(join_1);
	if (status == EACCES)
		status = 126;
	else if (status == ENOENT)
		status = 127;
	exit(status);
}

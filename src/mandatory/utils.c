/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/04 15:39:29 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

void	*init_pipex(void)
{
	static	t_pipex	pipex;

	return (&pipex);
}

void	ft_error(t_pipex *pipex, char *exec, char *message, int status)
{
	char	*join;

	join = ft_strjoin(exec, message);
	ft_putstr_fd(join, 2);
	free(join);
	pipex->status = status;
	exit(status);
}

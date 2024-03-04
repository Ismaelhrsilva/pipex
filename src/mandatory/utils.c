/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/04 17:18:14 by ishenriq         ###   ########.fr       */
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
	char	*join_1;
	char	*join_wline;

	join_1 = ft_strjoin(exec, ": ");
	join = ft_strjoin(join_1, message);
	join_wline = ft_strjoin(join, "\n");
	ft_putstr_fd(join_wline, 2);
	free(join);
	free(join_1);
	free(join_wline);
	pipex->status = status;
	exit(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/03 20:09:36 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

void	*init_pipex(void)
{
	static	t_pipex	pipex;

	return (&pipex);
}

void	ft_error(char *exec, char *message, int status)
{
	char	*join_1;
	char	*join_2;

	join_1 = ft_strjoin(exec, ": ");
	join_2 = ft_strjoin(join_1, message);
	ft_putstr_fd(join_2, 2);
	free(join_1);
	free(join_2);
	exit(status);
}

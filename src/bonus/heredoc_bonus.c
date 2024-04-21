/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/04/21 16:10:12 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/pipex_bonus.h"

char	*ft_heredoc(t_pipex *pipex)
{
	char	*gnl;
	int		size;

	pipex->infile = open(TEMP, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->infile < 0)
		ft_error(pipex, pipex->inf, strerror(errno), 1);
	while (1)
	{
		ft_printf("> ");
		gnl = get_next_line(STDIN_FILENO);
		size = ft_strlen(gnl) - 1;
		if (gnl && !ft_strncmp(gnl, pipex->argv[2], size))
			break ;
		ft_putstr_fd(gnl, pipex->infile);
		free(gnl);
	}
	free(gnl);
	pipex->argv++;
	pipex->argc--;
	pipex->flag = O_APPEND;
	close(pipex->infile);
	return (TEMP);
}

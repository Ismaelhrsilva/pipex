/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/10 18:05:07 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/pipex_bonus.h"

void	ft_pipex(t_pipex *pipex)
{
	while (pipex->ncmd++ < pipex->argc)
	{
		ft_printf("%d\n", pipex->ncmd);
		if (pipe(pipex->fds[pipex->ncmd - 2]) == -1)
			ft_error(pipex, "Pipe", strerror(errno), 1);
		pipex->pid = fork();
		if (pipex->pid == -1)
			ft_error(pipex, "Fork", strerror(errno), 1);
		if (pipex->pid == 0 && pipex->ncmd == 2)
			child(pipex, INFILE);
		else if (pipex->pid == 0 && pipex->ncmd == pipex->argc)
			child(pipex, OUTFILE);
		else if (pipex->pid == 0)
			child(pipex, MIDFILE);
		if (pipex->ncmd > 2)
			close_fds(pipex->fds[pipex->ncmd - 3]);
	}
	close_fds(pipex->fds[pipex->ncmd - 3]);
	if (pipex->pid > 0)
		ft_exit(pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = init_pipex();
	if (argc < 5)
		ft_error(pipex, "Pipex: " ,"Expected more than 5 arguments", 1);
	pipex->envp = envp;
	pipex->outf = argv[argc - 1];
	pipex->ncmd = 1;
	pipex->argv = argv;
	pipex->argc = argc - 2;
	pipex->inf = argv[1];
	construct_fds(pipex);
	ft_pipex(pipex);
	return (0);
}

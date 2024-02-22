/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/02/22 19:41:49 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

static t_pipex	*init_pipex(void)
{
	static t_pipex	pipex;

	return (&pipex);
}

static void	error(char* message, int num)
{
	int	size;

	size = ft_strlen(message);
	write(STDERR_FILENO, message, size);
	exit(num);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = init_pipex();
	if (argc > 5)
		error("More arguments than needed", 1);
	else if (argc < 5)
		error("Less arguments than needed", 1);
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	return (0);
}

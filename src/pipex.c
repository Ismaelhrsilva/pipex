/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/02/22 18:41:06 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipex	init_pipex(void)
{
	t_pipex	pipex;

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
	t_pipex	pipex;

	pipex = init_pipex();
	if (argc > 5)
		error("More arguments than needed", 1);
	else if (argc < 5)
		error("Less arguments than needed", 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/02/22 20:06:07 by ishenriq         ###   ########.fr       */
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

static void	get_envp(t_pipex *pipex)
{
	char const *s;
	char	**split;
	char	*join;
	int		i;

	i = 0;
	s = (char const *)pipex->envp;
	split = ft_split(s, ':');
	while (split[0])
	{
		join = ft_strjoin(split[0], "ls");
		if(!access(join, F_OK))
			ft_printf("Sucess");
		else
			free(join);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = init_pipex();
	//if (argc > 5)
	//	error("More arguments than needed", 1);
	//else if (argc < 5)
	//	error("Less arguments than needed", 1);
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	get_envp(pipex);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/03 20:09:47 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

void	ft_envp(t_pipex *pipex, char *exec, int cmd)
{
	int		i;
	char	**split;
	char	*f_bar;
	char	*filename_access;

	i = 0;
	while (pipex->envp[i] != NULL)
	{
		if (ft_strncmp(pipex->envp[i], "PATH=", 5) == 0)
		{
			pipex->path = (pipex->envp[i] + 6);
			break ;
		}
		else
			i++;
	}
	i = 0;
	split = ft_split(pipex->path, ':');
	while (split[i] != NULL)
	{
		f_bar = ft_strjoin(split[i], "/");
		filename_access = ft_strjoin(f_bar, exec);
		if (access(filename_access, F_OK | X_OK) == 0)
		{
			pipex->filename[cmd] = filename_access;
			free(f_bar);
			break ;
		}
		else
		{	
			free(f_bar);
			free(filename_access);
		}
		i++;
	}
	free(split);
}

void	get_cmd(t_pipex *pipex)
{
	char	**cmd1;
	char	**cmd2;

	ft_split_quote(ft_strdup(pipex->argv[2]), &cmd1);
	ft_split_quote(ft_strdup(pipex->argv[3]), &cmd2);
	pipex->cmd1_argv = cmd1;
	pipex->cmd2_argv = cmd2;
}

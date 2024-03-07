/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/06 22:22:48 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

static int	type_of_cmd(t_pipex *pipex, char *exec, int cmd)
{
	if (exec && ft_strncmp(exec, "/", 1) == 0)
	{
		if (access(exec, F_OK | X_OK) == 0)
		{
			pipex->filename[cmd] = exec;
			return (0);
		}
		else
			return (1);
	}
	else
		return (1);
}

static void	get_filename(t_pipex *pipex, char **split, char *exec, int cmd)
{
	char	*f_bar;
	char	*filename_access;
	int		i;

	i = 0;
	while (split[i] != NULL)
	{
		f_bar = ft_strjoin(split[i], "/");
		filename_access = ft_strjoin(f_bar, exec);
		if (filename_access && access(filename_access, F_OK | X_OK) == 0)
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

void	ft_envp(t_pipex *pipex, char *exec, int cmd)
{
	int		i;
	char	**split;

	i = 0;
	if (type_of_cmd(pipex, exec, cmd))
	{
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
		get_filename(pipex, split, exec, cmd);
	}
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

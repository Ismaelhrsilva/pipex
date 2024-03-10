/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/10 17:24:24 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/pipex_bonus.h"

static int	type_of_cmd(t_pipex *pipex, char *exec)
{
	if (exec && ft_strncmp(exec, "/", 1) == 0)
	{
		if (access(exec, F_OK | X_OK) == 0)
		{
			pipex->type_filename = 1;
			pipex->filename = exec;
			return (0);
		}
		else
			return (1);
	}
	else
		return (1);
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i] != NULL)
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

void	get_filename(t_pipex *pipex, char **split, char *exec)
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
			pipex->type_filename = 0;
			pipex->filename = filename_access;
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
	free_split(split);
}

void	ft_envp(t_pipex *pipex, char *exec)
{
	int		i;
	char	**split;

	i = 0;
	if (type_of_cmd(pipex, exec))
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
		get_filename(pipex, split, exec);
	}
}

void	get_cmd(t_pipex *pipex)
{
	char	*cd;

	cd = ft_strdup(pipex->argv[pipex->ncmd - 1]);
	pipex->cmd_argv = ft_split_quote(cd);
	free(cd);
}

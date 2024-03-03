/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/03 16:40:02 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

static void	ft_ast(t_node *root, t_pipex *pipex)
{
	if (root == NULL)
		return ;
	if (root->t == 2)
	{
		if (root->type == NODE_CMD)
		{
			execve(pipex->filename[1], pipex->cmd2_argv, pipex->envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	if (root->t == 1)
	{
		if (root->type == NODE_CMD)
		{
			execve(pipex->filename[0], pipex->cmd1_argv, pipex->envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pipex->pid_left = fork();
	if (pipex->pid_left == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pipex->pid_left == 0)
	{
		left_child(pipex);
		ft_ast(root->left, pipex);
	}
	if (pipex->pid_left > 0)
	{
		pipex->pid_right = fork();
		if (pipex->pid_right == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pipex->pid_right == 0)
		{
			right_child(pipex);
			ft_ast(root->right, pipex);
		}
		if (pipex->pid_right > 0)
		{
			ft_printf("Tratamentos aqui");
		}
		wait(NULL);
	}
}

static void	ft_envp(t_pipex *pipex, char *exec, int cmd)
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

static void get_cmd(t_pipex *pipex)
{
	pipex->cmd1_argv = ft_split(pipex->argv[2], ' ');	
	pipex->cmd2_argv = ft_split(pipex->argv[3], ' ');	
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = init_pipex();
	pipex->envp = envp;
	pipex->argv = argv;
	get_cmd(pipex);
	ft_envp(pipex, pipex->cmd1_argv[0], 0);
	ft_envp(pipex, pipex->cmd2_argv[0], 1);
	pipex->cmd1 = create_cmd_node(pipex->cmd1_argv, 1);
	pipex->cmd2 = create_cmd_node(pipex->cmd2_argv, 2);
	pipex->pipenode = create_pipe_node(pipex);

	ft_ast(pipex->pipenode, pipex);
	free_ast(pipex->pipenode);
	return (0);
}

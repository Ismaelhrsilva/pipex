/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/04 20:33:20 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

static void	ft_ast(t_node *root, t_pipex *pipex)
{
	int	status;

	if (root == NULL)
		return ;
	if (root->t == 2)
	{
		if (root->type == NODE_CMD)
		{
			execve(pipex->filename[1], pipex->cmd2_argv, pipex->envp);
			ft_error(pipex, "Execve", "Execve", 1);
		}
	}
	if (root->t == 1)
	{
		if (root->type == NODE_CMD)
		{
			execve(pipex->filename[0], pipex->cmd1_argv, pipex->envp);
			ft_error(pipex, "Execve", "Execve", 1);
		}
	}
	if (pipe(pipex->pipe_fd) == -1)
		ft_error(pipex, "Pipe", "Pipe", 1);
	pipex->pid_left = fork();
	if (pipex->pid_left == -1)
		ft_error(pipex, "Fork", "Fork", 1);
	if (pipex->pid_left == 0)
	{
		left_child(pipex);
		ft_ast(root->left, pipex);
	}
	pipex->pid_right = fork();
	if (pipex->pid_right == -1)
		ft_error(pipex, "Fork", "Fork", 1);
	if (pipex->pid_right == 0)
	{
		right_child(pipex);
		ft_ast(root->right, pipex);
	}
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		waitpid(-1, &status, 0); 
		exit(WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = init_pipex();
	if (argc != 5)
		ft_error(pipex, "Expected", "./pipex <infile> <cmd1> <cmd2> <oufile>", 1);
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

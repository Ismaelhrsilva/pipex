/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/06 21:45:06 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

static void	ft_node(t_node *root, t_pipex *pipex)
{
	int	fd;

	if (root->t == 2)
	{
		if (root->type == NODE_CMD)
		{
			fd = open(pipex->cmd2_argv[0], O_DIRECTORY | O_RDONLY, 0644);
			if (fd != -1)
			{
				close(fd);
				if (pipex->cmd2_argv[0] && ft_strchr(pipex->cmd2_argv[0], '/'))
					ft_error(pipex, pipex->cmd2_argv[0], "Is a directory", 126);
				ft_error(pipex, pipex->cmd2_argv[0], "command not found", 127);
			}
			if (pipex->filename[1] && access(pipex->filename[1] , F_OK | X_OK) == 0 \
			&& execve(pipex->filename[1], pipex->cmd2_argv, pipex->envp) < 0)
				ft_error(pipex, pipex->argv[3], strerror(errno), 127);
			if (pipex->cmd2_argv[0] && access(pipex->cmd2_argv[0], F_OK) == 0)
				if (execve(pipex->cmd2_argv[0], pipex->cmd2_argv, pipex->envp) < 0)
					ft_error(pipex, pipex->argv[3], strerror(errno), 126);
			if (pipex->cmd2_argv[0] && pipex->cmd2_argv[0][0] == '/')
				ft_error(pipex, &pipex->argv[3][0], "No such file or directory", 127);
			ft_error(pipex, pipex->argv[3], "command not found", 127);
		}
	}
	if (root->t == 1)
	{
		if (root->type == NODE_CMD)
		{
			fd = open(pipex->cmd1_argv[0], O_DIRECTORY | O_RDONLY, 0644);
			if (fd != -1)
			{
				close(fd);
				if (pipex->cmd1_argv[0] && ft_strchr(pipex->cmd1_argv[0], '/'))
					ft_error(pipex, pipex->cmd1_argv[0], "Is a directory", 126);
				ft_error(pipex, pipex->cmd1_argv[0], "command not found", 127);
			}
			if (pipex->filename[0] && access(pipex->filename[0] , F_OK | X_OK) == 0 \
			&& execve(pipex->filename[0], pipex->cmd1_argv, pipex->envp) < 0) 
				ft_error(pipex, pipex->argv[2], strerror(errno), 127);
			if (pipex->cmd1_argv[0] && access(pipex->cmd1_argv[0], F_OK) == 0)
				if (execve(pipex->cmd1_argv[0], pipex->cmd1_argv, pipex->envp) < 0)
					ft_error(pipex, pipex->argv[2], strerror(errno), 126);

			if (pipex->cmd1_argv[0] && pipex->cmd1_argv[0][0] == '/')
				ft_error(pipex, &pipex->argv[2][0], "No such file or directory", 127);
			ft_error(pipex, pipex->argv[2], "command not found", 127);
		}
	}
}

static void	ft_ast(t_node *root, t_pipex *pipex)
{
	int	status;

	if (root == NULL)
		return ;
	ft_node(root, pipex);
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
	pipex->pid_left = fork();
	if (pipex->pid_left == -1)
		ft_error(pipex, "Fork", "Fork", 1);
	if (pipex->pid_left == 0)
	{
		right_child(pipex);
		ft_ast(root->right, pipex);
	}
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pipex->pid_left, &status, 0); 
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(status);
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

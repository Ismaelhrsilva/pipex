/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/02/29 19:47:50 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

static t_node	*create_cmd_node(char **args, int t)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
	{
		perror("Node");
		exit(1);
	}
	node->type = NODE_CMD;
	node->args = args;
	node->left = NULL;
	node->right = NULL;
	node->t = t;
	return (node);
}

static t_node	*create_pipe_node(t_pipex pipex)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
	{
		perror("Node");
		exit(1);
	}
	node->type = NODE_PIPE;
	node->left = pipex->cmd1;
	node->right = pipex->cmd2;
	node->t = 0;
	node->args = NULL;
	return (node);
}

static void	free_ast(t_node *root)
{
	if (root == NULL)
		return ;
	free_ast(root->left);
	free_ast(root->right);
	free(root);
}

static void	ft_ast(t_node *root, t_pipex pipex)
{
	if (root == NULL)
		return ;
	if (root->t == 2)
	{
		if (root->type == NODE_CMD)
		{
			execve("/usr/bin/wc", (char *[]) {"wc", "-l", NULL}, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	if (root->t == 1)
	{
		if (root->type == NODE_CMD)
		{
			execve("/usr/bin/cat", (char *[]) {"cat", NULL}, NULL);
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
		close(pipex->pipe_fd[0]);
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipex->pipe_fd[1]);
		ft_ast(root->left, pipex);
	}
	else if (pipex->pid_left > 0)
	{
		pipex->pid_right = fork();
		if (pipex->pid_right == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pipex->pid_right == 0)
		{
			close(pipex->pipe_fd[1]);
			pipex->outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (pipex->outfile == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			close(pipex->pipe_fd[0]);
			ft_ast(pipex->root->right, argv);
		}
		if (pipex->pid_right > 0)
		{
			ft_printf("Tratamentos aqui");
		}
		wait(NULL);
	}
}

static	*init_pipex(void)
{
	static	t_pipex	pipex;

	return (&pipex);
}

int	main(int argc, char **argv)
{
	char	*args1[] = {argv[2], NULL};
	char	*args2[] = {argv[3], NULL};
	t_pipex	pipex;

	pipex = init_pipex();
	pipex->cmd1 = create_cmd_node(args1, 1);
	pipex->cmd2 = create_cmd_node(args2, 2);
	pipex->pipenode = create_pipe_node(pipex);
	pipex->argv = argv;

	ft_ast(pipex->pipenode, pipex);
	free_ast(pipex->pipenode);
	return (0);
}

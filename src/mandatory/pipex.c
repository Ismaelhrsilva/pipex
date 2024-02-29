/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/02/28 21:19:16 by ishenriq         ###   ########.fr       */
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

static t_node	*create_pipe_node(t_node *left, t_node *right)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
	{
		perror("Node");
		exit(1);
	}
	node->type = NODE_PIPE;
	node->left = left;
	node->right = right;
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

static void	ft_ast(t_node *root, char **argv)
{
	int	pipe_fd[2];
	pid_t	pid;

	if (root == NULL)
		return ;
	if (root->t == 1)
	{
		if (root->type == NODE_CMD)
		{
			execve("/usr/bin/wc", (char *[]) {"wc", "-l", NULL}, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	if (root->t == 2)
	{
		if (root->type == NODE_CMD)
		{
			execve("/usr/bin/ls", (char *[]) {"ls", "-la", NULL}, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (root->t == 1)
		{
			close(pipe_fd[0]);
			int	infile = open(argv[1], O_RDONLY);
			if (infile == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			if (dup2(infile, STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			close(pipe_fd[1]);
		}
		ft_ast(root->right, argv);
	}
	else if (pid > 0)
	{
		//if (root->t == 2)
		//{
			close(pipe_fd[1]);
			int	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (outfile == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			if (dup2(outfile, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			close(pipe_fd[0]);
		//}
		ft_ast(root->left, argv);
		wait(NULL);
	}
}

int	main(int argc, char **argv)
{
	char	*args1[] = {argv[2], NULL};
	char	*args2[] = {argv[3], NULL};

	t_node *cmd1 = create_cmd_node(args1, 1);
	t_node *cmd2 = create_cmd_node(args2, 2);
	t_node *pipenode = create_pipe_node(cmd1, cmd2);

	ft_ast(pipenode, argv);
	free_ast(pipenode);
	return (0);
}

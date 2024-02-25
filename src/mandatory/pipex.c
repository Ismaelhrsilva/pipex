/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/02/25 16:41:45 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

static t_node	*create_cmd_node(char **args)
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

static void	ft_ast(t_node *root)
{
	int	pipe_fd[2];
	pid_t	pid;

	if (root == NULL)
		return ;
	if (root->type == NODE_CMD)
	{
		execve(root->args[0], root->args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
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
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		ft_ast(root->right);
	}
	else if (pid > 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		ft_ast(root->left);
		wait(NULL);
	}
}

int	main(void)
{
	char	*args1[] = {"ls", NULL};
	char	*args2[] = {"wc", "-l", NULL};

	t_node *cmd1 = create_cmd_node(args1);
	t_node *cmd2 = create_cmd_node(args2);
	t_node *pipenode = create_pipe_node(cmd1, cmd2);

	ft_ast(pipenode);

	free_ast(pipenode);
	return (0);
}

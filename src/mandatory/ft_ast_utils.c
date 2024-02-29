/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:24:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/02/29 20:05:38 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/pipex.h"

t_node	*create_cmd_node(char **args, int t)
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

t_node	*create_pipe_node(t_pipex *pipex)
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

void	free_ast(t_node *root)
{
	if (root == NULL)
		return ;
	free_ast(root->left);
	free_ast(root->right);
	free(root);
}

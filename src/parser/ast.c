/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:09:24 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/22 19:27:02 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

static t_ast_node	*init_ast(t_ast_node *node, t_node_type type);

t_ast_node	*create_ast_node(t_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (init_ast(node, type));
}

void	free_ast_node(t_ast_node *root)
{
	if (!root)
		return ;
	if (root->type == NODE_CMD)
		free_cmd(root->u_content.cmd);
	else if (root->type == NODE_PIPE)
	{
		free_ast_node(root->u_content.s_pipe.left);
		free_ast_node(root->u_content.s_pipe.right);
	}
	else if (root->type == NODE_LIST)
		free_node_list(root);
	else if (root->type == NODE_SUBSHELL)
		free_ast_node(root->u_content.subshell);
	else if (root->type == NODE_OR || root->type == NODE_AND)
	{
		free_ast_node(root->u_content.s_binary.left);
		free_ast_node(root->u_content.s_binary.right);
	}
	else if (root->type == NODE_BACKGROUND)
		free_ast_node(root->u_content.s_background.cmd);
	free(root);
}

static t_ast_node	*init_ast(t_ast_node *node, t_node_type type)
{
	if (type == NODE_OR || type == NODE_AND)
	{
		node->u_content.s_binary.left = NULL;
		node->u_content.s_binary.right = NULL;
	}
	else if (type == NODE_LIST)
	{
		node->u_content.s_list.count = 0;
		node->u_content.s_list.size = 0;
		if (!alloc_commands(node))
			return (NULL);
	}
	else if (type == NODE_SUBSHELL)
		node->u_content.subshell = NULL;
	else if (type == NODE_PIPE)
	{
		node->u_content.s_pipe.left = NULL;
		node->u_content.s_pipe.right = NULL;
	}
	else if (type == NODE_BACKGROUND)
		node->u_content.s_background.cmd = NULL;
	else if (type == NODE_CMD)
		node->u_content.cmd = NULL;
	return (node);
}

static void	print_tabs(int n)
{
	int	i;

	i = -1;
	while (++i < n)
		printf("\t");
}

static char	*stringfy_node_type(t_node_type type)
{
	if (type == NODE_AND)
		return ("NODE_AND");
	if (type == NODE_OR)
		return ("NODE_OR");
	if (type == NODE_LIST)
		return ("NODE_LIST");
	if (type == NODE_BACKGROUND)
		return ("NODE_BACKGROUND");
	if (type == NODE_PIPE)
		return ("NODE_PIPE");
	if (type == NODE_CMD)
		return ("NODE_CMD");
	if (type == NODE_SUBSHELL)
		return ("NODE_SUBSHELL");
	return ("NONE");
}

void	print_ast(t_ast_node *root, int depth)
{
	if (!root)
		return ;
	print_tabs(depth);
	printf("%s:", stringfy_node_type(root->type));
	if (root->type != NODE_CMD)
		printf("\n");
	if (root->type == NODE_OR || root->type == NODE_AND)
	{
		print_ast(root->u_content.s_binary.left, depth + 1);
		print_ast(root->u_content.s_binary.right, depth + 1);
	}
	else if (root->type == NODE_LIST)
	{
		int	i = -1;
		while (++i < root->u_content.s_list.count)
			print_ast(root->u_content.s_list.commands[i], depth + 1);
	}
	else if (root->type == NODE_SUBSHELL)
		print_ast(root->u_content.subshell, depth + 1);
	else if (root->type == NODE_PIPE)
	{
		print_ast(root->u_content.s_pipe.left, depth + 1);
		print_ast(root->u_content.s_pipe.right, depth + 1);
	}
	else if (root->type == NODE_BACKGROUND)
		print_ast(root->u_content.s_background.cmd, depth + 1);
	else if (root->type == NODE_CMD)
		print_cmd(root->u_content.cmd);
}

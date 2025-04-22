/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:09:24 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/22 12:23:45 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*create_ast_node(t_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	if (type == NODE_OR || type == NODE_AND)
	{
		node->u_content.s_binary.left = NULL;
		node->u_content.s_binary.right = NULL;
	}
	else if (type == NODE_LIST)
	{
		node->u_content.s_list.count = 0;
		node->u_content.s_list.commands = NULL;
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
	return (node->type = type, node);
}

void	free_ast_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
		free_cmd(node->u_content.cmd);
	else if (node->type == NODE_PIPE)
	{
		free_ast_node(node->u_content.s_pipe.left);
		free_ast_node(node->u_content.s_pipe.right);
	}
}

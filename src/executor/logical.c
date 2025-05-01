/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:53:36 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/01 11:17:01 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	exec_and(t_executor *executor, t_ast_node *node, t_ctx *ctx);
static int	exec_or(t_executor *executor, t_ast_node *node, t_ctx *ctx);

int	exec_logical(t_executor *executor, t_ast_node *node, t_ctx *ctx)
{
	int	ret;
	if (node->type == NODE_AND)
		ret = exec_and(executor, node, ctx);
	else if (node->type == NODE_OR)
		ret = exec_or(executor, node, ctx);
	return (ret);
}


static int	exec_and(t_executor *executor, t_ast_node *node, t_ctx *ctx)
{
	int	status;

	status = exec_node(executor, node->u_content.s_binary.left, ctx);
	if (executor->childs_count > 0)
		status = wait_for_children(executor);
	if (WEXITSTATUS(status) == 0)
	{
		status = exec_node(executor, node->u_content.s_binary.right, ctx);
		if (executor->childs_count > 0)
			status = wait_for_children(executor);
	}
	return (status);
}

static int	exec_or(t_executor *executor, t_ast_node *node, t_ctx *ctx)
{
	int	status;

	status = exec_node(executor, node->u_content.s_binary.left, ctx);
	if (executor->childs_count > 0)
		status = wait_for_children(executor);
	if (WEXITSTATUS(status) != 0)
	{
		status = exec_node(executor, node->u_content.s_binary.right, ctx);
		if (executor->childs_count > 0)
			status = wait_for_children(executor);
	}
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:53:36 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/27 17:51:10 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	exec_and(t_ast_node *node);
static int	exec_or(t_ast_node *node);

int	exec_logical(t_ast_node *node)
{
	int	ret;
	if (node->type == NODE_AND)
		ret = exec_and(node);
	else if (node->type == NODE_OR)
		ret = exec_or(node);
	return (ret);
}


static int	exec_and(t_ast_node *node)
{
	int	ret1;
	int	ret2;

	ret1 = exec(node->u_content.s_binary.left);
	if (ret1 == 0)
		ret2 = exec(node->u_content.s_binary.right);
	else
		return (ret1);
	return (ret2);
}

static int	exec_or(t_ast_node *node)
{
	int	ret1;
	int	ret2;

	ret1 = exec(node->u_content.s_binary.left);
	if (ret1 == 0)
		return (ret1);
	else
		ret2 = exec(node->u_content.s_binary.right);
	return (ret2);
}

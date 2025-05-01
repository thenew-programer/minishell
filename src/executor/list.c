/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:50:49 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/01 11:16:22 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_list(t_executor *executor, t_ast_node *node, t_ctx *ctx)
{
	int	i;
	int	status;

	i = 0;
	while (i < node->u_content.s_list.count)
	{
		status = exec_node(executor, node->u_content.s_list.commands[i], ctx);
		if (executor->childs_count > 0)
			status = wait_for_children(executor);
		i++;
	}
	return (status);
}

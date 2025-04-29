/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:59:58 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/27 17:49:56 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_pipe(t_executor *executor, t_ast_node *node, t_ctx ctx)
{
	int	childs;
	int	fd[2];

	childs = 0;
	if (pipe(fd) != 0)
		return (make_exec_error(executor, "pipe() failed.", 100), -1);
	executor->ctx.fd[STDOUT_FILENO] = fd[STDOUT_FILENO];
	executor->ctx.fd_close = fd[STDIN_FILENO];
	childs += exec_node(executor, node->u_content.s_pipe.left, ctx);
	ctx.fd[STDIN_FILENO] = fd[STDIN_FILENO];
	ctx.fd_close = fd[STDOUT_FILENO];
	childs += exec_node(executor, node->u_content.s_pipe.right, ctx);
	return (childs);
}

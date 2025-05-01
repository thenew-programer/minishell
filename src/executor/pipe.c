/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:59:58 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/01 11:10:49 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>

int	exec_pipe(t_executor *executor, t_ast_node *node, t_ctx *ctx)
{
	int		fd[2];
	t_ctx	lctx;
	t_ctx	rctx;

	if (pipe(fd) != 0)
		return (make_exec_error(executor, "pipe() failed.", 100), -1);
	lctx = *ctx;
	lctx.fd[STDOUT_FILENO] = fd[STDOUT_FILENO];
	lctx.fd_close = fd[STDIN_FILENO];
	exec_node(executor, node->u_content.s_pipe.left, &lctx);
	rctx = *ctx;
	rctx.fd[STDIN_FILENO] = fd[STDIN_FILENO];
	rctx.fd_close = fd[STDOUT_FILENO];
	exec_node(executor, node->u_content.s_pipe.right, &rctx);
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);
	return (0);
}

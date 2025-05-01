/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:42:00 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/01 11:17:09 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	init_executor(t_executor *executor);
static void	free_executor(t_executor *executor);

int	exec(t_ast_node *ast)
{
	t_executor	executor;
	int			status;
	t_ctx		ctx;

	if (!ast)
		return (0);
	if (init_executor(&executor) == -1)
		return (-1);
	ctx = (t_ctx){{0, 1}, -1};
	status = exec_node(&executor, ast, &ctx);
	if (executor.childs_count > 0)
		status = wait_for_children(&executor);
	free_executor(&executor);
	return (WEXITSTATUS(status));
}

int	exec_node(t_executor *executor, t_ast_node *node, t_ctx *ctx)
{
	int	status;
	int	pid;

	pid = 0;
	if (!node)
		return (0);
	if (node->type == NODE_LIST)
		status = exec_list(executor, node, ctx);
	else if (node->type == NODE_OR || node->type == NODE_AND)
		status = exec_logical(executor, node, ctx);
	else if (node->type == NODE_SUBSHELL)
		status = exec_subshell(executor, node, ctx);
	else if (node->type == NODE_PIPE)
		status = exec_pipe(executor, node, ctx);
	else if (node->type == NODE_CMD)
	{
		pid = exec_command(executor, node->u_content.cmd, ctx);
		if (ctx->fd[STDOUT_FILENO] == STDOUT_FILENO
			&& ctx->fd[STDIN_FILENO] == STDIN_FILENO)
			waitpid(pid, &status, 0);
	}
	return (status);
}

static int init_executor(t_executor *executor)
{
	executor->childs = malloc(sizeof(int) * MAX_CHILDS);
	if (!executor->childs)
		return (-1);
	executor->childs_count = 0;
	executor->childs_capacity = MAX_CHILDS;
	executor->has_error = 0;
	return (0);
}

static void	free_executor(t_executor *executor)
{
	executor->childs_count = 0;
	if (executor->childs_capacity > 0)
		free(executor->childs);
	executor->childs_capacity = 0;
}

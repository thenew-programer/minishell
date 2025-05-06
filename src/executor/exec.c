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

static void	init_executor(t_executor *executor, t_env_list *env);
static void	free_executor(t_executor *executor);

int	exec(t_ast_node *ast, t_env_list *env)
{
	t_executor	executor;
	int			status;
	t_ctx		ctx;

	if (!ast)
		return (0);
	init_executor(&executor, env);
	if (executor.has_error)
		return (make_exec_error(&executor, "malloc() failed", MALLOC_ERROR),
			print_exec_error(&executor));
	ctx = (t_ctx){{0, 1}, -1};
	status = exec_node(&executor, ast, &ctx);
	free_executor(&executor);
	if (executor.has_error)
		return (print_exec_error(&executor));
	return (WEXITSTATUS(status));
}

int	exec_node(t_executor *executor, t_ast_node *node, t_ctx *ctx)
{
	int	status;
	int	pid;

	if (executor->has_error)
		return (executor->error.code);
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
			status = wait_for_child(executor, pid);
	}
	return (status);
}

static void	init_executor(t_executor *executor, t_env_list *env)
{
	executor->has_error = 0;
	executor->childs = malloc(sizeof(int) * MAX_CHILDS);
	if (!executor->childs)
		make_exec_error(executor, "malloc() failed", MALLOC_ERROR);
	executor->childs_count = 0;
	executor->childs_capacity = MAX_CHILDS;
	executor->env = env;
}

static void	free_executor(t_executor *executor)
{
	executor->childs_count = 0;
	if (executor->childs_capacity > 0)
		free(executor->childs);
	executor->childs_capacity = 0;
}

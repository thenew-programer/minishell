/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:42:00 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/27 18:15:00 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "exec.h"
#include <stdlib.h>
#include <sys/wait.h>

static void init_executor(t_executor *executor);

int	exec(t_ast_node *ast)
{
	t_executor	executor;
	int			childs;
	int			status;
	t_ctx		ctx;

	if (!ast)
		return (0);
	if (ast->type == NODE_LIST)
		childs = exec_list(ast);
	else if (ast->type == NODE_OR || ast->type == NODE_AND)
		childs = exec_logical(ast);
	else if (ast->type == NODE_SUBSHELL)
		childs = exec_subshell(ast);
	else
	{
		init_executor(&executor);
		ctx = (t_ctx){{0, 1}, -1};
		childs = exec_node(&executor, ast, ctx);
	}
	if (executor.has_error)
		return (print_exec_error(&executor), executor.error.code);
	while (childs--)
		wait(&status);
	return (WEXITSTATUS(status));
}

int	exec_node(t_executor *executor, t_ast_node *node, t_ctx ctx)
{
	int	childs;

	childs = 0;
	if (!node)
		return (childs);
	else if (node->type == NODE_PIPE)
		childs = exec_pipe(executor, node, ctx);
	else if (node->type == NODE_CMD)
		childs = exec_command(executor, node->u_content.cmd, ctx);
	return (childs);
}

static void init_executor(t_executor *executor)
{
	executor->has_error = 0;
}

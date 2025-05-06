/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:54:53 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/27 17:56:48 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_subshell(t_executor *executor, t_ast_node *node, t_ctx *ctx)
{
	int			status;
	t_env_list	*env_list;
	t_ctx		s_ctx;
	int			pid;

	pid = fork();
	if (pid == -1)
		return (make_exec_error(executor, "fork() failed", FORK_ERROR), FORK_ERROR);
	else if (pid == 0)
	{
		s_ctx = *ctx;
		apply_redirections(node->redir, &s_ctx);
		env_list = env();
		status = exec(node->u_content.subshell, env_list);
		free_env_list(env_list);
		exit(status);
	}
	waitpid(pid, &status, 0);
	return (status);
}

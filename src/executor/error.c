/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:05:31 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/27 17:08:10 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	make_exec_error(t_executor *executor, const char *msg, int code)
{
	if (executor->has_error)
		return ;
	executor->has_error = 1;
	executor->error.msg = msg;
	executor->error.code = code;
}

int	print_exec_error(t_executor *executor)
{
	fprintf(stderr, "minishell: %s\n", executor->error.msg);
	return (executor->error.code);
}

int	set_error(t_executor *executor, int status)
{
	if (status == DUP2_ERROR)
		return (make_exec_error(executor, "dup2() failed", DUP2_ERROR),
			DUP2_ERROR);
	if (status == PIPE_ERROR)
		return (make_exec_error(executor, "pipe() failed", PIPE_ERROR),
			PIPE_ERROR);
	if (status == MALLOC_ERROR)
		return (make_exec_error(executor, "malloc() failed", MALLOC_ERROR),
			MALLOC_ERROR);
	if (status == FORK_ERROR)
		return (make_exec_error(executor, "fork() failed", FORK_ERROR),
			FORK_ERROR);
	return (0);
}

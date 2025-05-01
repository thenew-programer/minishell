/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:07:19 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/01 11:08:56 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_command(t_executor *executor, t_cmd *cmd, t_ctx *ctx)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (make_exec_error(executor, "fork() failed", 100), -1);
	else if (pid == 0)
	{
		dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
		dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		int count = word_list_to_arr(cmd->args, NULL);
		char *dest[count + 1];
		word_list_to_arr(cmd->args, dest);
		execvp(cmd->name->str, dest);
		perror("minishell: ");
		exit(127);
	}
	add_child(executor, pid);
	return (pid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:07:19 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/27 18:43:03 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdio.h>
#include <unistd.h>

int	exec_command(t_executor *executor, t_cmd *cmd, t_ctx ctx)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (make_exec_error(executor, "fork() failed", 100), -1);
	else if (pid == 0)
	{
		dup2(STDIN_FILENO, ctx.fd[STDIN_FILENO]);
		dup2(STDOUT_FILENO, ctx.fd[STDOUT_FILENO]);
		if (ctx.fd_close >= 0)
			close(ctx.fd_close);
		int count = word_list_to_arr(cmd->args, NULL);
		char *dest[count + 1];
		word_list_to_arr(cmd->args, dest);
		execvp(cmd->name->str, dest);
		perror("");
	}
	return (1);
}

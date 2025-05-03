/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:07:19 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/03 11:50:22 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_command(t_executor *executor, t_cmd *cmd, t_ctx *ctx)
{
	int		pid;
	char	*err;

	pid = fork();
	if (pid == -1)
		return (make_exec_error(executor, "fork() failed", FORK_ERROR), FORK_ERROR);
	else if (pid == 0)
	{
		int ret = apply_redirections(cmd->redir, ctx);
		if (ret != 0)
			exit(ret);
		// if (ctx->fd[STDIN_FILENO] != STDIN_FILENO)
		// {
		// 	if (dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO) == -1)
		// 		exit(DUP2_ERROR);
		// }
		// if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
		// {
		// 	if (dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
		// 		exit(DUP2_ERROR);
		// }
		// if (ctx->fd_close >= 0)
		// 	close(ctx->fd_close);
		execvp(cmd->name->str, (char **){NULL});
		err = "command not found";
		if (errno != ENOENT)
			err = strerror(errno);
		fprintf(stderr, "minishell: %s: %s\n", cmd->name->str, err);
		exit(127);
	}
	add_child(executor, pid);
	return (pid);
}

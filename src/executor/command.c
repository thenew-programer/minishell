/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:07:19 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/03 14:30:13 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_command(t_executor *executor, t_cmd *cmd, t_ctx *ctx)
{
	int		pid;
	char	*err;
	char	**args;

	args = prepare_args(executor, cmd);
	if (!args)
		return (make_exec_error(executor, "malloc() failed", MALLOC_ERROR), MALLOC_ERROR);
	pid = fork();
	if (pid == -1)
		return (make_exec_error(executor, "fork() failed", FORK_ERROR), FORK_ERROR);
	else if (pid == 0)
	{
		int ret = apply_redirections(cmd->redir, ctx);
		if (ret != 0)
			exit(ret);
		execvp(cmd->name->str, args);
		err = "command not found";
		if (errno != ENOENT)
			err = strerror(errno);
		fprintf(stderr, "minishell: %s: %s\n", cmd->name->str, err);
		exit(127);
	}
	int	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
	add_child(executor, pid);
	return (pid);
}

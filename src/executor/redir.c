/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:28:37 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/03 11:49:30 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	open_file(char *filename, t_redir_type type);
static int	simple_redir(t_redir_list *redir, t_ctx *ctx);

int	apply_redirections(t_redir_list *redir, t_ctx *ctx)
{
	int	ret;

	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_OUT
			|| redir->type == APPEND_OUT)
		{
			ret = simple_redir(redir, ctx);
			if (ret != 0)
				return (ret);
		}
		else if (redir->type == HEREDOC)
			if (handle_heredoc(redir, ctx) == PIPE_ERROR)
				return (PIPE_ERROR);
		redir = redir->next;
	}
	if (ctx->fd[STDIN_FILENO] != STDIN_FILENO)
		if (dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO) == -1)
			return (DUP2_ERROR);
	if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
		if (dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
			return (DUP2_ERROR);
	if (ctx->fd_close > 0)
		close(ctx->fd_close);
	return (0);
}

static int	simple_redir(t_redir_list *redir, t_ctx *ctx)
{
	int	fd;
	int	redir_to;

	fd = open_file(redir->filename->str, redir->type);
	if (fd < 0)
		return (OPEN_ERROR);

	if (redir->type == REDIR_IN)
		redir_to = STDIN_FILENO;
	else if (redir->type == REDIR_OUT || redir->type == APPEND_OUT)
		redir_to = STDOUT_FILENO;
	if (dup2(fd, redir_to) == -1)
		return (close(fd), DUP2_ERROR);
	close(fd);
	if (redir->type == REDIR_IN)
		ctx->fd[STDIN_FILENO] = STDIN_FILENO;
	if (redir->type == REDIR_OUT || redir->type == APPEND_OUT)
		ctx->fd[STDOUT_FILENO] = STDOUT_FILENO;
	return (0);
}

static int	open_file(char *filename, t_redir_type type)
{
	int	fd;

	if (type == REDIR_IN)
		fd = open(filename, O_RDONLY);
	else if (type == REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
}

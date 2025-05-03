/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:21:21 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/03 09:54:10 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_heredoc(t_redir_list *redir, t_ctx *ctx)
{
	int		fd[2];
	char	*line;
	int		delim_len;

	(void)ctx;
	if (pipe(fd) == -1)
		return (PIPE_ERROR);
	delim_len = ft_strlen(redir->filename->str);
	write(1, "here_doc> ", 10);
	line = get_next_line(STDIN_FILENO);
	while (!line || ft_strncmp(redir->filename->str, line, delim_len) != 0)
	{
		write(fd[STDOUT_FILENO], line, ft_strlen(line));
		free(line);
		write(1, "here_doc> ", 10);
		line = get_next_line(STDIN_FILENO);
	}
	if (line)
		free(line);
	close(fd[STDOUT_FILENO]);
	dup2(fd[STDIN_FILENO], STDIN_FILENO);
	close(fd[STDIN_FILENO]);
	ctx->fd[STDIN_FILENO] = STDIN_FILENO;
	return (0);
}

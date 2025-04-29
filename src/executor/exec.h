/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:29:29 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/27 18:18:49 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../parser/parser.h"
# include "../scanner/scanner.h"
# include "env.h"

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_ctx
{
	int	fd[2];
	int	fd_close;
}	t_ctx;

typedef struct s_executor
{
	t_env_list	*env;
	t_error		error;
	int			has_error;
	t_ctx		ctx;
}	t_executor;

/* exec.c */
int	exec(t_ast_node *ast);
int	exec_node(t_executor *executor, t_ast_node *node, t_ctx ctx);

/* error.c */
void	make_exec_error(t_executor *executor, const char *msg, int code);
void	print_exec_error(t_executor *executor);

/* list.c */
int	exec_list(t_ast_node *node);

/* logical.c */
int	exec_logical(t_ast_node *node);

/* pipe.c */
int	exec_pipe(t_executor *executor, t_ast_node *node, t_ctx ctx);

/* subshell.c */
int	exec_subshell(t_ast_node *node);

/* command.c */
int exec_command(t_executor *executor, t_cmd *cmd, t_ctx ctx);

#endif /* EXEC_H */

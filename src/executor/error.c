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

void	print_exec_error(t_executor *executor)
{
	if (!executor->has_error)
		return ;
	fprintf(stderr, "minishell: %s\n", executor->error.msg);

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:53:10 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/01 11:10:44 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h>

void	add_child(t_executor *executor, int pid)
{
	int	*childs;
	int	i;

	if (executor->childs_count >= executor->childs_capacity)
	{
		executor->childs_capacity += MAX_CHILDS;
		childs = malloc(sizeof(int) * executor->childs_capacity);
		if (!childs)
			return ;
		i = -1;
		while (++i < executor->childs_count)
			childs[i] = executor->childs[i];
		free(executor->childs);
		executor->childs = childs;
	}
	executor->childs[executor->childs_count++] = pid;
}

int	wait_for_children(t_executor *executor)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (i < executor->childs_count)
	{
		waitpid(executor->childs[i], &status, 0);
		i++;
	}
	executor->childs_count = 0;
	return (status);
}

int	wait_for_child(t_executor *executor, int pid)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	while (++i < executor->childs_count)
		if (executor->childs[i] == pid)
			break ;
	if (i < executor->childs_count)
	{
		waitpid(pid, &status, 0);
		while (i < executor->childs_count - 1)
		{
			executor->childs[i] = executor->childs[i + 1];
			i++;
		}
		executor->childs_count--;
	}
	return (status);
}

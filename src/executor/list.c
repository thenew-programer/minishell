/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:50:49 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/27 17:51:27 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_list(t_ast_node *node)
{
	int	i;
	int	ret;

	i = 0;
	while (i < node->u_content.s_list.count)
		ret = exec(node->u_content.s_list.commands[i++]);
	return (ret);
}

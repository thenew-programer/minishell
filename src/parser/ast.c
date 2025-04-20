/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:36:55 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/20 15:39:31 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*init_ast(void)
{
	t_ast_node	*ast;

	ast = malloc(sizeof(t_ast_node));
	ast->type = PROGRAM;
	return (ast);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:51:48 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/22 11:57:15 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_logical(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*logical;

	left = malloc(sizeof(t_ast_node));
	if (!left)
		return (NULL);

	left = parse_pipeline(parser);
	if (!left)
		return (NULL);
	while (parser->curr.type == TOKEN_AND_AND
		|| parser->curr.type == TOKEN_OR)
	{
		t_node_type type = NODE_AND;
		if (parser->curr.type == TOKEN_OR)
			type = NODE_OR;
		right = parse_pipeline(parser);
		if (!right)
		{
			free(left);
			return (NULL);
		}
		logical = malloc(sizeof(t_ast_node));
		if (!logical)
			return (NULL);
		logical->type = type;
		logical->u_content.s_binary.left = left;
		logical->u_content.s_binary.right = right;
		left = logical;
	}
	return (left);
}

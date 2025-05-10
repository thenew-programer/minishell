/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:51:48 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/22 16:28:02 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_logical(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*logical;
	t_node_type	type;

	left = parse_pipeline(parser);
	if (!left)
		return (NULL);
	while (parser_match(parser, TOKEN_AND_AND)
		|| parser_match(parser, TOKEN_OR))
	{
		if (parser->curr.type == TOKEN_EOF || parser->curr.type == TOKEN_ERROR)
			return (make_error(parser, "", 2), left);
		type = (t_node_type)parser->prev.type;
		right = parse_pipeline(parser);
		if (!right)
			return (free_ast_node(left), NULL);
		logical = create_ast_node(type);
		if (!logical)
			return (free_ast_node(left), free_ast_node(right), NULL);
		logical->u_content.s_binary.left = left;
		logical->u_content.s_binary.right = right;
		left = logical;
	}
	return (left);
}

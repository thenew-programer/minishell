/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:09:24 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/22 16:25:44 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_pipeline(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*pipe;

	left = parse_command(parser);
	if (!left)
		return (NULL);
	while (parser_match(parser, TOKEN_PIPE))
	{
		right = parse_command(parser);
		if (!right)
			return (free_ast_node(left), NULL);
		pipe = create_ast_node(NODE_PIPE);
		if (!pipe)
			return (free_ast_node(left), free_ast_node(right), NULL);
		pipe->u_content.s_pipe.left = left;
		pipe->u_content.s_pipe.right = right;
		left = pipe;
	}
	return (left);
}

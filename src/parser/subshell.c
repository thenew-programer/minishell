/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:46:41 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/23 15:49:18 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_subshell(t_parser *parser)
{
	t_ast_node		*list;
	t_ast_node		*subshell;
	t_redir_list	*redir_list;

	if (parser_match(parser, TOKEN_LEFT_PAREN))
	{
		list = parse_list(parser);
		if (!list)
			return (NULL);
	}
	if (!parser_match(parser, TOKEN_RIGHT_PAREN))
	{
		make_error(parser, "", 2);
		return (free_ast_node(list), NULL);
	}
	subshell = create_ast_node(NODE_SUBSHELL);
	if (!subshell)
		return (free_ast_node(list), NULL);
	subshell->u_content.subshell = list;
	redir_list = NULL;
	while (is_redir(parser->curr.type))
		redir_list = parse_redir(&redir_list, parser);
	subshell->redir = redir_list;
	return (subshell);
}

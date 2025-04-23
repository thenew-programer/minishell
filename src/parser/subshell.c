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
	t_ast_node	*subshell;

	if (parser_match(parser, TOKEN_LEFT_PAREN))
		subshell = parse_list(parser);
	if (!parser_match(parser, TOKEN_RIGHT_PAREN))
		return (free_ast_node(subshell), NULL);
	return (subshell);
}

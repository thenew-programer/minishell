/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:38:32 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/22 19:35:10 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_command(t_parser *parser)
{
	t_ast_node	*command;
	t_ast_node	*subshell;

	if (parser->curr.type == TOKEN_WORD
		|| parser->curr.type == TOKEN_DQ_WORD
		|| parser->curr.type == TOKEN_SQ_WORD
		|| parser->curr.type == TOKEN_REDIR_IN
		|| parser->curr.type == TOKEN_REDIR_OUT
		|| parser->curr.type == TOKEN_APPEND_OUT
		|| parser->curr.type == TOKEN_HEREDOC)
	{
		command = parse_cmd(parser);
		if (!command)
			return (NULL);
	}
	else if (parser_match(parser, TOKEN_LEFT_PAREN))
	{
		subshell = parse_list(parser);
		if (!subshell)
			return (NULL);
		if (!parser_match(parser, TOKEN_RIGHT_PAREN))
			return (free_ast_node(subshell), NULL);
		command = create_ast_node(NODE_SUBSHELL);
		if (!command)
			return (NULL);
		command->u_content.subshell = subshell;
	}
	return (command);
}

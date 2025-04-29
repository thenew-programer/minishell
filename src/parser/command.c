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
	else if (parser->curr.type == TOKEN_LEFT_PAREN)
	{
		command = parse_subshell(parser);
		if (!command)
			return (NULL);
	}
	else
		return (make_error(parser, "", 2), NULL);
	return (command);
}

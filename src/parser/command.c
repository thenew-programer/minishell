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

	if (is_word(parser->curr.type) || is_redir(parser->curr.type))
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

int	is_word(t_token_type type)
{
	if (type == TOKEN_WORD || type == TOKEN_DQ_WORD
		|| type == TOKEN_SQ_WORD)
		return (1);
	return (0);
}

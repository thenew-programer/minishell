/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:38:32 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/22 12:05:51 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_command(t_parser *parser)
{
	t_ast_node	*command;
	t_cmd		*cmd;
	t_ast_node	*subshell;

	command = malloc(sizeof(t_ast_node));
	if (!command)
		return (NULL);
	if (parser->curr.type == TOKEN_WORD
		|| parser->curr.type == TOKEN_DQ_WORD
		|| parser->curr.type == TOKEN_SQ_WORD)
	{
		command->type = NODE_CMD;
		cmd = parse_cmd(parser);
		if (!cmd)
			return (free(command), NULL);
		command->u_content.cmd = cmd;
	}
	else if (parser_match(parser, TOKEN_LEFT_PAREN))
	{
		command->type = NODE_SUBSHELL;
		subshell = parse_list(parser);
		if (!subshell || parser->curr.type != TOKEN_RIGHT_PAREN)
			return (free(command), NULL);
		command->u_content.subshell = subshell;
	}
	else
		return (free(command), NULL);
	return (command);
}

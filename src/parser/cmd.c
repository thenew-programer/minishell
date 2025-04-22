/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:18:37 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/21 10:44:41 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->redir = NULL;
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->name)
		free_word(cmd->name);
	if (cmd->args)
		free_word_list(cmd->args);
	if (cmd->redir)
		free_redir_list(cmd->redir);
	free(cmd);
}

t_cmd	*parse_cmd(t_parser *parser)
{
	t_cmd			*cmd;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	parse_redir(&cmd->redir, parser);
	cmd->name = parse_word(parser);
	while ((parser->curr.type == TOKEN_WORD
		|| parser->curr.type == TOKEN_DQ_WORD
		|| parser->curr.type == TOKEN_SQ_WORD
		|| parser->curr.type == TOKEN_REDIR_IN
		|| parser->curr.type == TOKEN_REDIR_OUT
		|| parser->curr.type == TOKEN_APPEND_OUT
		|| parser->curr.type == TOKEN_HEREDOC)
		&& !parser->has_error)
	{
		parse_redir(&cmd->redir, parser);
		parse_word_list(&cmd->args, parser);
	}
	return (cmd);
}

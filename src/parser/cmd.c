/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:18:37 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/20 16:58:12 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*parse_cmd(t_parser *parser)
{
	t_cmd			*cmd;
	t_word			*word;
	t_word_list		*word_list;
	t_redir_list	*redir_list;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (parser->curr.type == TOKEN_SQ_WORD
		|| parser->curr.type == TOKEN_DQ_WORD
		|| parser->curr.type == TOKEN_WORD)
	{
		word = parse_word(parser);
		if (!word)
			return (free(cmd), NULL);
		while (parser->curr.type == TOKEN_SQ_WORD
		|| parser->curr.type == TOKEN_DQ_WORD
		|| parser->curr.type == TOKEN_WORD
		word_list = parse_word_list(parser);
		if (!word_list)
			return (free_word(word), free(cmd), NULL);
	}
	free(cmd);
	return (NULL);
}

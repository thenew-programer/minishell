/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:14:02 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/20 16:29:12 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parse_dqword(t_parser *parser, t_word *word);
static void	parse_sqword(t_parser *parser, t_word *word);


void	free_word(t_word *word)
{
	if (!word)
		return ;
	if (word->word)
		free(word->word);
	free(word);
}
t_word	*parse_word(t_parser *parser)
{
	t_word	*word;
	char	*str;

	word = (t_word *)malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	if (parser->curr.type == TOKEN_WORD)
	{
		word->word = strndup(parser->curr.start, parser->curr.len);
		word->flag = TOKEN_WORD;
	}
	else if (parser->curr.type == TOKEN_SQ_WORD)
		parse_sqword(parser, word);
	else if (parser->curr.type == TOKEN_DQ_WORD)
		parse_dqword(parser, word);
	parser_advance(parser);
	return (word);
}

static void	parse_dqword(t_parser *parser, t_word *word)
{
	word->word = strndup(parser->curr.start + 1, parser->curr.len - 2);
	word->flag = TOKEN_DQ_WORD;
}

static void	parse_sqword(t_parser *parser, t_word *word)
{
	word->word = strndup(parser->curr.start + 1, parser->curr.len - 2);
	word->flag = TOKEN_SQ_WORD;

}

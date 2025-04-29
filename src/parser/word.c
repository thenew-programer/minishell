/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:14:02 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/21 10:53:05 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_word	*parse_dqword(t_parser *parser);
static t_word	*parse_sqword(t_parser *parser);


t_word	*new_word(char *str, int flag)
{
	t_word	*word;

	word = (t_word *)malloc(sizeof(t_word));
	if (!word)
	{
		if (str)
			free(str);
		return (NULL);
	}
	word->str = str;
	word->flag = flag;
	return (word);
}

void	free_word(t_word *word)
{
	if (!word)
		return ;
	if (word->str)
		free(word->str);
	free(word);
}

t_word	*parse_word(t_parser *parser)
{
	char	*str;

	if (parser->curr.type == TOKEN_WORD)
	{
		str = malloc(sizeof(char) * parser->curr.len + 1);
		if (!str)
			return (NULL);
		str = strndup(parser->curr.start, parser->curr.len);
		parser_advance(parser);
		return (new_word(str, TOKEN_WORD));
	}
	else if (parser->curr.type == TOKEN_SQ_WORD)
		return (parse_sqword(parser));
	else if (parser->curr.type == TOKEN_DQ_WORD)
		return (parse_dqword(parser));
	return (NULL);
}

static t_word	*parse_dqword(t_parser *parser)
{
	char	*str;

	if (parser->curr.start[parser->curr.len - 1] != '"' && !parser->has_error)
	{
		make_error(parser, "", 0);
		return (NULL);
	}
	str = strndup(parser->curr.start + 1, parser->curr.len - 2);
	if (!str)
		return (NULL);
	parser_advance(parser);
	return (new_word(str, TOKEN_DQ_WORD));
}

static t_word	*parse_sqword(t_parser *parser)
{
	char	*str;

	if (parser->curr.start[parser->curr.len - 1] != '\'' && !parser->has_error)
	{
		make_error(parser, "", 0);
		return (NULL);
	}
	str = strndup(parser->curr.start + 1, parser->curr.len - 2);
	if (!str)
		return (NULL);
	parser_advance(parser);
	return (new_word(str, TOKEN_SQ_WORD));

}

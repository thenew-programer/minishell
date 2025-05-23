/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:39:27 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/18 15:47:48 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

t_token	make_token(t_scanner *scanner, t_token_type type)
{
	t_token	token;

	token.type = type;
	token.start = scanner->start;
	token.len = scanner->curr - scanner->start;
	token.line = scanner->line;
	return (token);
}

t_token	word(t_scanner *scanner)
{
	while (!ft_strchr("><()&|", peek(scanner)) && !ft_isspace(peek(scanner))
		&& !is_atend(scanner))
		advance(scanner);
	return (make_token(scanner, TOKEN_WORD));
}

t_token	string(t_scanner *scanner, int delim)
{
	t_token_type	type;

	while (peek(scanner) != delim && !is_atend(scanner))
	{
		if (peek(scanner) == '\n')
			scanner->line++;
		advance(scanner);
	}
	advance(scanner);
	type = TOKEN_SQ_WORD;
	if (delim == '"')
		type = TOKEN_DQ_WORD;
	return (make_token(scanner, type));
}

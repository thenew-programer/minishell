/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 05:51:04 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/18 15:47:22 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

static t_token	tokenize_sym(t_scanner *scanner, char c);
static t_token	tokenize(t_scanner *scanner, char c);

t_token	scan_token(t_scanner *scanner)
{
	char	c;

	skip_whitespace(scanner);
	scanner->start = scanner->curr;
	if (is_atend(scanner))
		return (make_token(scanner, TOKEN_EOF));
	c = advance(scanner);
	if (ft_isalnum(c))
		return (word(scanner));
	return (tokenize(scanner, c));
}

t_token_type	peeknext_token(t_scanner *scanner)
{
	t_token	token;

	token = scan_token(scanner);
	scanner->curr -= token.len;
	return (token.type);
}

void	init_scanner(t_scanner *scanner, const char *src)
{
	if (!scanner)
		return ;
	scanner->start = src;
	scanner->curr = src;
	scanner->line = 1;
}

static t_token	tokenize_sym(t_scanner *scanner, char c)
{
	if (c == '(')
		return (make_token(scanner, TOKEN_LEFT_PAREN));
	else if (c == ')')
		return (make_token(scanner, TOKEN_RIGHT_PAREN));
	else if (c == ';')
		return (make_token(scanner, TOKEN_SEMICOLAN));
	else if (c == '"')
		return (string(scanner, '"'));
	else if (c == '>')
	{
		if (peek(scanner) == '>')
			return (advance(scanner), make_token(scanner, TOKEN_APPEND_OUT));
		else
			return (make_token(scanner, TOKEN_REDIR_OUT));
	}
	else if (c == '<')
	{
		if (peek(scanner) == '<')
			return (advance(scanner), make_token(scanner, TOKEN_HEREDOC));
		else
			return (make_token(scanner, TOKEN_REDIR_IN));
	}
	else
		return (string(scanner, '\''));
}

static t_token	tokenize(t_scanner *scanner, char c)
{
	while (1)
	{
		if (ft_strchr("();\"'><", c))
			return (tokenize_sym(scanner, c));
		else if (c == '|')
		{
			if (peek(scanner) == '|')
				return (advance(scanner), make_token(scanner, TOKEN_OR));
			else
				return (make_token(scanner, TOKEN_PIPE));
		}
		else if (c == '&')
		{
			if (peek(scanner) == '&')
				return (advance(scanner), make_token(scanner, TOKEN_AND_AND));
			else
				return (make_token(scanner, TOKEN_ERROR));
		}
		else
			return (word(scanner));
	}
}

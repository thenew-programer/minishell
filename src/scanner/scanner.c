/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 05:51:04 by ybouryal          #+#    #+#             */
/*   Updated: 2025/03/30 06:04:25 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "scanner.h"

static t_token	make_token(t_scanner *scanner, t_token_type type);
static t_token	number(t_scanner *scanner);
static t_token	word(t_scanner *scanner);
static t_token	string(t_scanner *scanner, int delim);

void	init_scanner(t_scanner *scanner, const char *src)
{
	if (!scanner)
		return ;
	scanner->start = src;
	scanner->curr = src;
	scanner->line = 1;
}

t_token	scan_token(t_scanner *scanner)
{
	char	c;

	skip_whitespace(scanner);
	scanner->start = scanner->curr;
	if (is_atend(scanner))
		return (make_token(scanner, TOKEN_EOF));
	c = advance(scanner);
	if (ft_isdigit(c))
		return (number(scanner));
	if (is_alpha(c))
		return (word(scanner));
	while (1)
	{
		if (c == '(')
			return (make_token(scanner, TOKEN_LEFT_PAREN));
		else if (c == ')')
			return (make_token(scanner, TOKEN_RIGHT_PAREN));
		else if (c == '[')
			return (make_token(scanner, TOKEN_LEFT_SBRACE));
		else if (c == ']')
			return (make_token(scanner, TOKEN_RIGHT_SBRACE));
		else if (c == '{')
			return (make_token(scanner, TOKEN_LEFT_CBRACE));
		else if (c == '}')
			return (make_token(scanner, TOKEN_RIGHT_CBRACE));
		else if (c == '>')
		{
			if (peek_next(scanner) == '>')
				return (advance(scanner), make_token(scanner, TOKEN_APPEND));
			else
				return (make_token(scanner, TOKEN_REDIR_RIGHT));
		}
		else if (c == '<')
		{
			if (peek_next(scanner) == '<')
				return (advance(scanner), make_token(scanner, TOKEN_HEREDOC));
			else
				return (make_token(scanner, TOKEN_REDIR_LEFT));
		}
		else if (c == '|')
		{
			if (peek_next(scanner) == '|')
				return (advance(scanner), make_token(scanner, TOKEN_OR));
			else
				return (make_token(scanner, TOKEN_PIPE));
		}
		else if (c == '&')
		{
			if (peek_next(scanner) == '&')
				return (advance(scanner), make_token(scanner, TOKEN_AND_AND));
			else
				return (make_token(scanner, TOKEN_AND));
		}
		else if (c == ';')
			return (make_token(scanner, TOKEN_SEMICOLAN));
		else if (c == '=')
			return (make_token(scanner, TOKEN_EQUAL));
		else if (c == '"')
			return (string(scanner, '"'));
		else if (c == '\'')
			return (string(scanner, '\''));
		else
			return (word(scanner));
	}
}

static t_token	make_token(t_scanner *scanner, t_token_type type)
{
	t_token	token;

	token.type = type;
	token.start = scanner->start;
	token.len = scanner->curr - scanner->start;
	token.line = scanner->line;
	return (token);
}

static t_token	number(t_scanner *scanner)
{
	while (!is_atend(scanner) && ft_isdigit(peek(scanner)))
			advance(scanner);
	return (make_token(scanner, TOKEN_NBR));
}

static t_token	word(t_scanner *scanner)
{
	while ((is_alpha(peek(scanner)) || ft_isdigit(peek(scanner)))
		&& !is_atend(scanner))
		advance(scanner);
	return (make_token(scanner, TOKEN_WORD));
}

static t_token	string(t_scanner *scanner, int delim)
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

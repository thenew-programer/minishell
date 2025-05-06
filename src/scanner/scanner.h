/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 05:43:48 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/18 15:46:34 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "../libft.h"

typedef enum e_token_type
{
	TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_PAREN,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND_OUT,
	TOKEN_HEREDOC,
	TOKEN_AND_AND,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_PIPE,
	TOKEN_SEMICOLAN,
	TOKEN_SQ_WORD,
	TOKEN_DQ_WORD,
	TOKEN_WORD,
	TOKEN_ERROR,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	const char		*start;
	int				len;
	int				line;
}	t_token;

typedef struct s_scanner
{
	const char	*start;
	const char	*curr;
	int			line;
}	t_scanner;

void			init_scanner(t_scanner *scanner, const char *src);

t_token			scan_token(t_scanner *scanner);

t_token_type	peeknext_token(t_scanner *scanner);

int				advance(t_scanner *scanner);

int				peek(t_scanner *scanner);

int				peek_next(t_scanner *scanner);

int				is_atend(t_scanner *scanner);

int				match(t_scanner *scanner, char c);

void			skip_whitespace(t_scanner *scanner);

int				is_alpha(int c);

t_token			make_token(t_scanner *scanner, t_token_type type);

t_token			number(t_scanner *scanner);

t_token			word(t_scanner *scanner);

t_token			string(t_scanner *scanner, int delim);

#endif /* SCANNER_H */

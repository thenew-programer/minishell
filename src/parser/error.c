/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:07:35 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/21 10:53:13 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	make_error(t_parser *parser, const char *msg, int code)
{
	if (parser->has_error)
		return ;
	parser->has_error = 1;
	parser->error.msg = msg;
	parser->error.code = code;
	parser->error.ctx = parser->scanner->curr;
}

void	print_error(t_parser *parser)
{
	if (parser->curr.type == TOKEN_EOF)
		fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
	else
		fprintf(stderr, "minishell: syntax error near unexpected token `%.*s'\n", parser->curr.len, parser->curr.start);
}

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
	parser->error.msg = msg;
	parser->error.code = code;
	parser->error.ctx = parser->scanner->curr;
}

void	print_error(t_parser *parser)
{
	int		i;
	char	ut;

	if (!parser->has_error)
		return ;
	else if (parser->has_error && parser->error.code == 0)
		return ;
	i = 0;
	ut = parser->error.ctx[i];
	while ((ut == ' ' || ut == '\t') && parser->error.ctx[i])
		ut = parser->scanner->curr[i++];
	if (ut == 0)
		fprintf(stderr, "bash: syntax error near unexpected token `newline'\n");
	else
		fprintf(stderr, "bash: syntax error near unexpected token `%c'\n", ut);
}

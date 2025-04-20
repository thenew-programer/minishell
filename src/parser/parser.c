/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:58:52 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/20 16:17:43 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

/*
t_ast_node	*parse(const char *src)
{
	t_ast_node	*ast;
	t_scanner	scanner;
	t_token		token;

	init_scanner(&scanner, src);
	token = scan_token(&scanner);
	while (1)
	{
		printf("%.*s", token.len, token.start);
		printf(" - type = %d\n", token.type);
		token = scan_token(&scanner);
		if (token.type == TOKEN_EOF)
		{
			printf("\n");
			break ;
		}
	}
	return (ast);
}
*/

void	init_parser(t_parser *parser, t_scanner *scanner)
{
	parser->scanner = scanner;
	parser->curr = scan_token(scanner);
	parser->prev = parser->curr;
	parser->ast = NULL;
}

int	parser_match(t_parser *parser, t_token_type type)
{
	if (peeknext_token(parser->scanner) == type)
	{
		parser->prev = parser->curr;
		parser->curr = scan_token(parser->scanner);
		return (1);
	}
	return (0);
}
void	parser_advance(t_parser *parser)
{
	parser->prev = parser->curr;
	parser->curr = scan_token(parser->scanner);
}

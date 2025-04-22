/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:58:52 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/22 20:09:25 by ybouryal         ###   ########.fr       */
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
	parser->has_error = 0;
}

void	parser_advance(t_parser *parser)
{
	parser->prev = parser->curr;
	parser->curr = scan_token(parser->scanner);
}

int	parser_match(t_parser *parser, t_token_type type)
{
	if (peeknext_token(parser->scanner) == type)
	{
		parser_advance(parser);
		return (1);
	}
	return (0);
}

t_ast_node	*parse(const char *src)
{
	t_parser	parser;
	t_scanner	scanner;
	t_ast_node	*ast;

	init_scanner(&scanner, src);
	init_parser(&parser, &scanner);
	ast = parse_list(&parser);
	if (parser.has_error) {
		print_error(&parser);
		return (free_ast_node(ast), NULL);
	}
	return (ast);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:58:52 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/18 20:08:01 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"
#include <string.h>

void	parse(const char *src)
{
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
}

char	*parse_word(t_scanner *scanner, t_token token)
{
	char	*str;

	if (token.type != TOKEN_WORD)
		return ((void *)-1);
	return (strndup(token.start, token.len));
}

char	*parse_name(t_scanner *scanner, t_token token)
{
	return (parse_word(scanner, token));
}

t_assignode	*parse_assign(t_scanner *scanner, t_token token)
{
	t_assignode	*node;
	t_token	next;
	char	*name;
	char	*word;

	node = malloc(sizeof(t_assignode));
	if (!node)
		return (NULL);
	parse_name(scanner, token);
	if (name)
	{
		if (peeknext_token(scanner) == TOKEN_EQUAL)
		{
			scan_token(scanner);
			if (peeknext_token(scanner) == TOKEN_WORD || peeknext_token(scanner) == TOKEN) {

			}
			word = parse_word(scanner, token);
			if (word) {
				node->word = word;
				node->name = name;
				return (node);
			}
		}
	}
	return (node);
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:48:31 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/22 11:50:57 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_list(t_parser *parser)
{
	t_ast_node	*list;
	t_ast_node	*list;

	list = malloc(sizeof(t_ast_node));
	if (!list)
		return (NULL);
	list = parse_logical(parser);
	while (parser->curr.type == TOKEN_SEMICOLAN)
	{

	}
	return (list);
}

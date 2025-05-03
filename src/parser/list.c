/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:48:31 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/22 20:21:36 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define MAX_COMMANDS 100

static t_ast_node	*extend_commands(t_ast_node *list);

void	free_node_list(t_ast_node *node)
{
	int	i;

	if (!node->u_content.s_list.commands)
		return ;
	i = 0;
	while (i < node->u_content.s_list.count)
		free_ast_node(node->u_content.s_list.commands[i++]);
	free(node->u_content.s_list.commands);
}

t_ast_node	*parse_list(t_parser *parser)
{
	t_ast_node	*node;
	t_ast_node	*list;

	list = create_ast_node(NODE_LIST);
	if (!list)
		return (NULL);
	node = parse_logical(parser);
	if (!node)
		return (free_ast_node(list), NULL);
	list->u_content.s_list.commands[list->u_content.s_list.count++] = node;
	while (parser_match(parser, TOKEN_SEMICOLAN))
	{
		if (parser->curr.type == TOKEN_EOF)
			return (list);
		if (list->u_content.s_list.count == list->u_content.s_list.size)
			if (extend_commands(list) == NULL)
				return (free_ast_node(list), NULL);
		node = parse_logical(parser);
		if (!node)
			return (free_ast_node(list), NULL);
		list->u_content.s_list.commands[list->u_content.s_list.count++] = node;
	}
	return (list);
}

static t_ast_node	*extend_commands(t_ast_node *node)
{
	int			new_size;
	t_ast_node	**commands;
	int			i;

	new_size = node->u_content.s_list.size * 2;
	commands = malloc(sizeof(t_ast_node *) * new_size);
	if (!commands)
		return (free_ast_node(node), NULL);
	i = -1;
	while (++i < node->u_content.s_list.count)
		commands[i] = node->u_content.s_list.commands[i];
	node->u_content.s_list.size = new_size;
	free(node->u_content.s_list.commands);
	node->u_content.s_list.commands = commands;
	return (node);
}

t_ast_node	*alloc_commands(t_ast_node *node)
{
	t_ast_node	**commands;

	commands = malloc(sizeof(t_ast_node *) * MAX_COMMANDS);
	if (!commands)
		return (free_ast_node(node), NULL);
	node->u_content.s_list.commands = commands;
	return (node);
}

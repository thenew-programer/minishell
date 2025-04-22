/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:46:58 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/21 10:51:18 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_redir_list	*new_redir_list(char *op, char *filename)
{
	t_redir_list	*new;

	new = malloc(sizeof(t_redir_list));
	if (!new)
		return (NULL);
	new->op = op;
	new->filename = filename;
	new->next = NULL;
	return (new);
}

static t_redir_list	*append_redir_list(t_redir_list *head, t_redir_list *new)
{
	t_redir_list	*curr;

	if (!head)
		return (new);
	curr = head;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	return (head);
}

t_redir_list	*parse_redir(t_redir_list **list, t_parser *parser)
{
	char			*op;
	char			*filename;
	t_redir_list	*new;

	if (parser->curr.type == TOKEN_REDIR_IN
		|| parser->curr.type == TOKEN_REDIR_OUT
		|| parser->curr.type == TOKEN_APPEND_OUT
		|| parser->curr.type == TOKEN_HEREDOC)
	{
		op = strndup(parser->curr.start, parser->curr.len);
		if (parser_match(parser, TOKEN_WORD) 
			|| parser_match(parser, TOKEN_SQ_WORD)
			|| parser_match(parser, TOKEN_DQ_WORD))
		{
			filename = strndup(parser->curr.start, parser->curr.len);
			new = new_redir_list(op, filename);
			if (!new)
				return (free(filename), free(op), NULL);
			*list = append_redir_list(*list, new);
			parser_advance(parser);
			return (*list);
		}
		free(op);
		if (!parser->has_error) {
			make_error(parser, "", 2);
			parser->has_error = 1;
		}
	}
	return (NULL);
}

void	free_redir_list(t_redir_list *list)
{
	t_redir_list	*next;

	if (!list)
		return ;
	while (list)
	{
		next = list->next;
		free(list->filename);
		free(list->op);
		free(list);
		list = next;
	}
}

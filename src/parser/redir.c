/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:46:58 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/25 11:03:17 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_redir_list	*new_redir_list(t_redir_type type, t_word *filename)
{
	t_redir_list	*new;

	new = malloc(sizeof(t_redir_list));
	if (!new)
		return (NULL);
	new->type = type;
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
	t_redir_type	type;
	t_word			*filename;
	t_redir_list	*new;

	if (is_redir(parser->curr.type))
	{
		type = (t_redir_type)parser->curr.type;
		parser_advance(parser);
		if (is_word(parser->curr.type))
		{
			filename = parse_word(parser);
			if (!filename)
				return (NULL);
			new = new_redir_list(type, filename);
			if (!new)
				return (free(filename), *list);
			*list = append_redir_list(*list, new);
			return (*list);
		}
		make_error(parser, "", 2);
	}
	return (*list);
}

void	free_redir_list(t_redir_list *list)
{
	t_redir_list	*next;

	if (!list)
		return ;
	while (list)
	{
		next = list->next;
		free_word(list->filename);
		free(list);
		list = next;
	}
}

int	is_redir(t_token_type type)
{
	if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND_OUT || type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

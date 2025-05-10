/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:29:07 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/27 18:48:52 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_word_list	*new_word_list(t_word *word)
{
	t_word_list	*list;

	list = malloc(sizeof(t_word_list));
	if (!list)
		return (NULL);
	list->word = word;
	list->next = NULL;
	return (list);
}

t_word_list	*append_word_list(t_word_list *head, t_word_list *new)
{
	t_word_list	*last;

	if (!head)
		return (new);
	last = head;
	while (last->next)
		last = last->next;
	last->next = new;
	return (head);
}

void	free_word_list(t_word_list *head)
{
	t_word_list	*curr;
	t_word_list	*next;

	if (!head)
		return ;
	curr = head;
	while (curr)
	{
		next = curr->next;
		free_word(curr->word);
		free(curr);
		curr = next;
	}
}

t_word_list	*parse_word_list(t_word_list **list, t_parser *parser)
{
	t_word_list	*new;
	t_word		*word;

	while (parser->curr.type == TOKEN_WORD
		|| parser->curr.type == TOKEN_DQ_WORD
		|| parser->curr.type == TOKEN_SQ_WORD
		|| parser->curr.type == TOKEN_ERROR)
	{
		word = parse_word(parser);
		if (!word)
			return (free_word_list(*list), NULL);
		new = new_word_list(word);
		if (!new)
			return (free_word_list(*list), NULL);
		*list = append_word_list(*list, new);
	}
	return (*list);
}

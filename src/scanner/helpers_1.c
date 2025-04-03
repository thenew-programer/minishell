/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 05:53:24 by ybouryal          #+#    #+#             */
/*   Updated: 2025/03/30 06:18:40 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

int	advance(t_scanner *scanner)
{
	char	c;

	if (!scanner || is_atend(scanner))
		return (0);
	c = *scanner->curr;
	scanner->curr++;
	return (c);
}

int	peek(t_scanner *scanner)
{
	if (!scanner || is_atend(scanner))
		return (0);
	return (*scanner->curr);
}

int	peek_next(t_scanner *scanner)
{
	if (!scanner || is_atend(scanner))
		return (0);
	return (*(scanner->curr + 1));
}

int	is_atend(t_scanner *scanner)
{
	if (!scanner || *scanner->curr == '\0')
		return (1);
	return (0);
}

int	match(t_scanner *scanner, char c)
{
	if (!scanner || is_atend(scanner))
		return (0);
	if (*scanner->curr != c)
		return (0);
	advance(scanner);
	return (1);
}

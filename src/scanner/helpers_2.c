/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 06:06:26 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/18 15:45:07 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	skip_whitespace(t_scanner *scanner)
{
	char	c;
	char	tmp;

	while (1)
	{
		c = peek(scanner);
		if (c == '\t' || c == '\r' || c == ' ')
			advance(scanner);
		else if (c == '\n')
		{
			scanner->line++;
			advance(scanner);
		}
		else if (c == '#')
		{
			tmp = c;
			while (!is_atend(scanner) && tmp != '\n')
				tmp = advance(scanner);
		}
		else
			return ;
	}
}

int	is_alpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| c == '_' || c == '.' || c == '/')
		return (1);
	return (0);
}

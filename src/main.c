/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 05:39:34 by ybouryal          #+#    #+#             */
/*   Updated: 2025/03/30 05:42:00 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char		*src;
	t_scanner	scanner;
	t_token		token;

	while (1)
	{
		src = readline("> ");
		token.type = 0;
		init_scanner(&scanner, src);
		while (1)
		{
			if (token.type == TOKEN_EOF)
			{
				printf("\n");
				break ;
			}
			token = scan_token(&scanner);
			printf("%*s", token.len, token.start);
			printf(" - type = %d\n", token.type);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 05:39:34 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/22 20:11:46 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"

int	main()
{
	char			*src;
	t_ast_node		*ast;

	while (1)
	{
		src = readline("> ");
		ast = parse(src);
		if (ast)
		{
			print_ast(ast, "", true);
			free_ast_node(ast);
		}
		free(src);
	}
	return (0);
}

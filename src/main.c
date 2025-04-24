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
#include <signal.h>
#include <readline/history.h>
#include <stdio.h>

int	g_interrupted;

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		g_interrupted = 1;

		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init()
{
	g_interrupted = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

int	main()
{
	char			*src;
	t_ast_node		*ast;

	init();
	while (1)
	{
		src = readline("> ");
		if (g_interrupted)
		{
			g_interrupted = 0;
			free(src);
			continue;
		}
		if (!src)
			return (printf("exit\n"), 0);
		else
		{
			int t = 0;
			for (int i = 0; src[i]; i++)
				if (src[i] != ' ' || !(src[i] >= 9 && src[i] <= 13))
					t = 1;
			if (t == 0)
			{
				free(src);
				continue;
			}
		}

		ast = parse(src);
		if (ast)
		{
			print_ast(ast, "", true);
			free_ast_node(ast);
		}
		add_history(src);
		free(src);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 05:39:34 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/25 11:01:31 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/exec.h"
#include "minishell.h"
#include "parser/parser.h"
#include <readline/history.h>
#include <readline/readline.h>

sig_atomic_t	g_interrupted;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_interrupted = 1;

		rl_done = 1;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		// rl_set_prompt("$> ");
		rl_redisplay();
	}
}

void	init()
{
	g_interrupted = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

int	main()
{
	char		*src;
	t_ast_node	*ast;

	init();
	while (1)
	{
		// src = readline("$> ");
		src = prompt();
		if (!src)
			break ;
		if (g_interrupted)
		{
			g_interrupted = 0;
			free(src);
			continue;
		}
		else
		{
			int t = 0;
			for (int i = 0; src[i]; i++)
				if (!ft_isspace(src[i]))
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
			int s = exec(ast);
			printf("--exit status: %d--\n", s);
			free_ast_node(ast);
		}
		add_history(src);
		free(src);
	}
	printf("exit\n");
	rl_clear_history();
	return (0);
}

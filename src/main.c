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

#include "minishell.h"

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
		rl_set_prompt("$> ");
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
	int			lstatus;

	init();
	while (1)
	{
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

		ast = parse(src, &lstatus);
		if (lstatus == 1)
			break ;
		if (ast)
		{
			lstatus = exec(ast);
			free_ast_node(ast);
			if (lstatus >= EXECVE_ERROR && lstatus <= OPEN_ERROR)
				break ;
		}
		add_history(src);
		free(src);
	}
	printf("exit\n");
	rl_clear_history();
	return (lstatus);
}

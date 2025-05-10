/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:55:36 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/06 11:03:05 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_interrupt(char *src);
static int	is_empty_line(char *src);
static void	cleanup(t_env *env_list);

int repl(void)
{
	char		*src;
	t_ast_node	*ast;
	int			lstatus;
	t_env		env;

	new_env(&env);
	init();
	while (1)
	{
		src = prompt();
		if (!src)
			break ;
		if (handle_interrupt(src) || is_empty_line(src))
			continue;
		ast = parse(src, &lstatus);
		if (ast)
		{
			lstatus = exec(ast, &env);
			free_ast_node(ast);
			if (lstatus >= EXECVE_ERROR && lstatus <= PIPE_ERROR)
				break ;
		}
		add_history(src);
		free(src);
	}
	cleanup(&env);
	return lstatus;
}

static int handle_interrupt(char *src)
{
	if (g_interrupt)
	{
		g_interrupt = 0;
		free(src);
		return (1);
	}
	return (0);
}

static int	is_empty_line(char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (!ft_isspace(src[i]))
			return (0);
		i++;
	}
	free(src);
	return (1);
}

static void	cleanup(t_env *env_list)
{
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	free_env(env_list);
	rl_clear_history();
}

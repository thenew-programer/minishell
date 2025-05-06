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
static int	should_exit(t_ast_node *ast, int lstatus);
static int	execute_if_valid(t_ast_node *ast, t_env_list *env_list, int prev_status);
static void	cleanup(t_env_list *env_list);

int repl(void)
{
	char		*src;
	t_ast_node	*ast;
	int			lstatus;
	t_env_list	*env_list;

	init();
	env_list = env();
	while (1)
	{
		src = prompt(PROMPT);
		if (!src)
			break ;
		if (handle_interrupt(src))
			continue;
		if (is_empty_line(src))
			continue;
		ast = parse(src, &lstatus);
		if (should_exit(ast, lstatus))
			break;
		lstatus = execute_if_valid(ast, env_list, lstatus);
		add_history(src);
		free(src);
	}
	cleanup(env_list);
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

static int	should_exit(t_ast_node *ast, int lstatus)
{
	return (ast && lstatus >= EXECVE_ERROR && lstatus <= OPEN_ERROR);
}

static int	execute_if_valid(t_ast_node *ast, t_env_list *env_list, int prev_status)
{
	int status = prev_status;
	if (ast)
	{
		status = exec(ast, env_list);
		free_ast_node(ast);
	}
	return (status);
}

static void	cleanup(t_env_list *env_list)
{
	printf("exit\n");
	free_env_list(env_list);
	rl_clear_history();
}

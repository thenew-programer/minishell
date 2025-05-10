/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:03:16 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/06 11:03:51 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t	g_interrupt;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_interrupt = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init(void)
{
	g_interrupt = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 05:39:57 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/06 11:04:12 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser/parser.h"
# include "scanner/scanner.h"
# include "executor/exec.h"
# include "libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>

# define PROMPT	" $> "

extern sig_atomic_t	g_interrupt;

typedef struct s_shell
{
	int	lstatus;
}	t_shell;

/* prompt.c */
char	*prompt(char *p);

/* init.c */
void	init(void);

#endif /* MINISHELL_H */

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
#define MINISHELL_H

#include "executor/exec.h"
#include "libft.h"
#include "parser/parser.h"
#include "scanner/scanner.h"

#include <sys/ioctl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

#define PROMPT "--% "

extern sig_atomic_t g_interrupt;

/* prompt.c */
char	*prompt(void);

/* init.c */
void	init(void);

/* rppl.c */
int 	repl(void);

#endif /* MINISHELL_H */

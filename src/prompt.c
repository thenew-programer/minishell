/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:54:53 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/25 11:02:04 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EOF_ERROR "minishell: syntax error: unexpected end of file\n"
#define M_ERROR "minishell: malloc error\n"

static char	*read_full_line(void);
static char	*append_line(char *full, char *line);
static int	is_line_atend(char *full);

char	*prompt(void)
{
	char	*src;

	src = read_full_line();
	return (src);
}

static char	*read_full_line(void)
{
	char	*line;
	char	*full;
	int		idx;

	// if (isatty(STDIN_FILENO))
	// 	printf("%s", PROMPT);
	line = readline(PROMPT);
	if (!line || g_interrupt)
		return (line);
	full = ft_strdup(line);
	free(line);
	if (!full)
		return (write(1, EOF_ERROR, 48) , NULL);
	while (1)
	{
		idx = is_line_atend(full);
		if (idx == 0)
			return (full);
		// if (isatty(STDIN_FILENO))
		// 	printf("> ");
		line = readline("> ");
		if (!line)
			return (write(1, EOF_ERROR, 48), free(full), NULL);
		if (g_interrupt)
			return (free(line), full);
		full = append_line(full, line);
		if (!full)
			return (write(1, M_ERROR, 24), NULL);
	}
}

static int	is_line_atend(char *full)
{
	int	idx;
	int	tmp;

	idx = ft_strlen(full) - 1;
	while (idx >= 0 && ft_isspace(full[idx]))
		idx--;
	tmp = idx - 2;
	while (tmp >= 0 && ft_isspace(full[tmp]))
		tmp--;
	if (tmp <= 0 || idx < 0)
		return (0);
	if ((full[idx] == '|' && idx > 0 && full[idx - 1] == '|') ||
		(full[idx] == '&' && idx > 0 && full[idx - 1] == '&'))
		return (idx);
	if (full[idx] == '|' || full[idx] == ';')
		return (idx);
	return (0);
}
static char	*append_line(char *full, char *line)
{
	char	*new;

	new = ft_strjoin(full, line);
	free(full);
	free(line);
	return (new);
}

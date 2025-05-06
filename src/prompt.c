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

static char	*read_full_line(const char *prompt);

char	*prompt(char *p)
{
	char	*pwd;
	char	*src;

	pwd = getcwd(NULL, 0);
	p = ft_strjoin(pwd , p);
	free(pwd);
	src = read_full_line(p);
	free(p);
	return (src);
}

static char	*read_full_line(const char *prompt)
{
	char	*line;
	char	*full_line;
	int		idx;
	int		tmp;

	if (!prompt)
		prompt = "$> ";
	line = readline(prompt);
	if (!line)
		return (NULL);
	if (g_interrupted)
		return (line);
	full_line = ft_strdup(line);
	free(line);
	while (1)
	{
		idx = ft_strlen(full_line) - 1;
		while (idx >= 0 && ft_isspace(full_line[idx]))
			idx--;
		if (idx == 0
			|| (full_line[idx] != '|' && full_line[idx] != ';' && full_line[idx] != '&'))
			return (full_line);
		tmp = idx - 2;
		while (tmp >= 0 && ft_isspace(line[tmp]))
			tmp--;
		if (tmp == 0)
			return (full_line);
		if ((full_line[idx - 1] == '|' && full_line[idx] == '|')
			|| (full_line[idx] == '&' && full_line[idx - 1] == '&')
			|| full_line[idx] == ';' || full_line[idx] == '|')
		{
			line = readline("> ");
			if (!line)
			{
				fprintf(stderr, "minishell: syntax error: unexpected end of file\n");
				return (free(full_line), NULL);
			}
			if (g_interrupted)
				return (free(line), full_line);
		}
		else
			return (full_line);
		full_line = ft_strjoin(full_line, line);
		free(line);
		if (!full_line)
			return (fprintf(stderr, "minishell: malloc error\n"), NULL);
	}
}

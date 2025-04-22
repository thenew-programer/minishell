/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 05:39:34 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/21 10:54:07 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"

int	main()
{
	char		*src;
	t_cmd		*cmd;
	t_word_list	*wlist;
	t_redir_list *rlist;

	while (1)
	{
		src = readline("> ");
		cmd = parse(src);
		if (!cmd)
			continue;
		wlist = cmd->args;
		rlist = cmd->redir;
		printf("cmd: %s\n", cmd->name->str);
		printf("args: ");
		while (wlist)
		{
			printf("%s ", wlist->word->str);
			wlist = wlist->next;
		}
		printf("\nredir: ");
		while (rlist)
		{
			printf("%s %s", rlist->op, rlist->filename);
			rlist = rlist->next;
			if (rlist != NULL)
				printf(" - ");
		}
		printf("\n");
		free_cmd(cmd);
		free(src);
	}
	return (0);
}

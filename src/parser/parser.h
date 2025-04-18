/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 05:42:13 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/18 20:08:57 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../scanner/scanner.h"
# include "stdio.h"

typedef struct s_assignode
{
	char	*name;
	char	*word;
}	t_assignode;

typedef struct	s_astnode
{
	t_token	token;
	union data {
		t_assignode	*node;
	};
}	t_astnode;

void	parse(const char *src);

#endif /* PARSER_H */

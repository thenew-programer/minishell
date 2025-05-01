/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:56:35 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/30 10:02:16 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../parser/parser.h"

extern char **environ;

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

typedef struct s_env_list
{
	t_env				*var;
	struct s_env_list	*next;
}	t_env_list;

#endif /* ENV_H */

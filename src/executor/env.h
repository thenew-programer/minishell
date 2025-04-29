/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:56:35 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/27 14:58:47 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../parser/parser.h"

typedef struct s_env
{
	t_word	*name;
	t_word	*value;
}	t_env;

typedef struct s_env_list
{
	t_env				*var;
	struct s_env_list	*next;
}	t_env_list;

#endif /* ENV_H */

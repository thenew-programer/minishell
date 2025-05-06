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

/* env.c */
char		*get_env_value(t_env_list *env, char *str, int len);
int			set_env(t_env_list *list, char *env_var);
t_env		*get_env(t_env_list *list, char *name);
void		free_env_list(t_env_list *list);
t_env_list	*env(void);

#endif /* ENV_H */

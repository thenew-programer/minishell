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
	char	**env;
	size_t	count;
	size_t	capacity;
}	t_env;


/* env.c */
t_env	*new_env(t_env *env);
char	*get_env(t_env *env, char *name);
int		set_env(t_env *env, char *name, char *value);
int		unset_env(t_env *env, char *name);
void	free_env(t_env *env);

#endif /* ENV_H */

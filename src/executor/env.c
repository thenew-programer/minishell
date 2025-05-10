/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:55:18 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/30 14:07:41 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static size_t	copy_env(char **env, size_t len);

t_env	*new_env(t_env *env)
{
	size_t		len;

	len = -1;
	while (environ[++len]);
	env->capacity = len * 2;
	env->env = ft_calloc(sizeof(char *), env->capacity);
	if (!env->env)
		return (env->env = NULL, env);
	env->count = copy_env(env->env, len);
	if (env->count == 0)
	{
		free(env->env);
		env->env = NULL;
	}
	return (env);
}

static size_t	copy_env(char **env, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
	{
		env[i] = ft_strdup(environ[i]);
		if (!env[i])
			break ;
	}
	if (i == len)
		return (env[i] = NULL, i);
	while (i > 0)
	{
		free(env[i--]);
		if (i == 0)
			return (free(env[i]), 0);
	}
	return (0);
}

char	*get_env(t_env *env, char *name)
{
	size_t	i;
	size_t		name_len;
	char	*value;

	if (!name || !*name || !ft_strchr(name, '='))
		return (ft_strdup(""));
	name_len = ft_strlen(name);
	i = -1;
	while (++i < env->count)
		if (ft_strncmp(env->env[i], name, name_len) == 0)
			break ;
	if (!env->env[i])
		return (ft_strdup(""));
	value = ft_strdup(env->env[i] + name_len);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

int	set_env(t_env *env, char *name, char *value)
{
	size_t		i;
	char	**new_env;

	if (!ft_strchr(name, '='))
		return (1);
	if (env->count >= env->capacity)
	{
		new_env = malloc(sizeof(char *) * (env->capacity * 2));
		if (!new_env)
			return (1);
		i = -1;
		while (++i <= env->count)
			new_env[i] = env->env[i];
		free(env->env);
		env->env = new_env;
	}
	env->env[env->count++] = ft_strjoin(name, value);
	return (0);
}

int	unset_env(t_env *env, char *name)
{
	size_t	name_len;
	size_t	i;

	if (!name)
		return (1);
	name_len = ft_strlen(name);
	i = -1;
	while (++i < env->count)
		if (ft_strncmp(env->env[i], name, name_len) == 0)
			break ;
	if (i >= env->count)
		return (1);
	free(env->env[i]);
	while (i < env->count)
	{
		env->env[i] = env->env[i + 1];
		i++;
	}
	env->count--;
	return (0);
}

void	free_env(t_env *env)
{
	size_t	i;

	i = -1;
	while (++i < env->count)
		free(env->env[i]);
	free(env->env);
	env->capacity = 0;
	env->count = 0;
}

/*
int	main()
{
	t_env env;
	new_env(&env);
	if (!env.env)
		return (prsize_tf("malloc failed\n"), 0);
	for (size_t i = 0; i < env.count; i++)
		prsize_tf("[%d] %s\n", i, env.env[i]);

	char *value = get_env(&env, "HOME=");
	free(value);
	prsize_tf("get_env('HOME') = %s\n", value);
	size_t ret = set_env(&env, "jos=", "Youssef");
	prsize_tf("set_env('jos=', 'Youssef') = %s\n", ret ? "False": "True");
	for (size_t i = 0; i < env.count; i++)
		prsize_tf("[%d] %s\n", i, env.env[i]);
	ret = unset_env(&env, "jos=");
	prsize_tf("unset_env('jos=') = %s\n", ret ? "False": "True");
	for (size_t i = 0; i < env.count; i++)
		prsize_tf("[%d] %s\n", i, env.env[i]);
	free_env(&env);
	return (0);
}
*/

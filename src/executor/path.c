/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 08:43:51 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/10 09:04:14 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*build_path(char *path, char *name);

char	*resolve_path(t_executor *executor, char *arg)
{
	char		*path;
	struct stat	sb;

	if (stat(arg, &sb) == 0 && S_ISREG(sb.st_mode) && access(arg, X_OK) == 0)
		return (arg);
	if (ft_strchr(arg, '/'))
		return (arg);
	char *env = get_env(executor->env, "PATH=");
	if (!env)
		return (arg);
	char **values = ft_split(env, ':');
	free(env);
	if (!values || !*values)
		return (free(values), arg);
	int	i = 0;
	while (values[i])
	{
		path = build_path(values[i], arg);
		if (stat(path, &sb) == 0 && S_ISREG(sb.st_mode) && access(path, X_OK) == 0)
			break ;
		free(path);
		path = arg;
		i++;
	}
	i = 0;
	while (values[i])
		free(values[i++]);
	free(values);
	return (path);
}

static char	*build_path(char *path, char *name)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	path = ft_strjoin(tmp, name);
	free(tmp);
	return (path);
}

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
#include <string.h>

static t_env_list	*append_env(t_env_list *env_list, t_env_list *new_env_list);
static t_env_list	*new_env_list(char *env);
static void			free_env_list(t_env_list *list);
static void			free_env_var(t_env *env_var);
t_env				*prepare_env_var(char *env_var);
t_env				*get_env(t_env_list *list, char *name);
int					set_env(t_env_list *list, char *env_var);

int	set_env(t_env_list *list, char *env_var)
{
	t_env_list	*env_elm;
	t_env		*tmp;

	tmp = get_env(list, env_var);
	if (!tmp)
	{
		env_elm = new_env_list(env_var);
		if (!env_elm)
			return (-1);
		list = append_env(list, env_elm);
	}
	else
	{
		while (list)
		{
			if (ft_strncmp(list->var->name, tmp->name, ft_strlen(tmp->name) + 1))
			{
				tmp = prepare_env_var(env_var);
				free_env_var(list->var);
				list->var = tmp;
				break ; 
			}
			list = list->next;
		}
	}
	return (0);
}

t_env	*get_env(t_env_list *list, char *name)
{
	while (list)
	{
		if (ft_strncmp(list->var->name, name, ft_strlen(list->var->name)) == 0)
			return (list->var);
		list = list->next;
	}
	return (NULL);
}

t_env_list	*env(void)
{
	t_env_list	*env_list;
	t_env_list	*tmp;
	int			i;

	i = 0;
	env_list = NULL;
	while (environ[i])
	{
		tmp = new_env_list(environ[i]);
		if (!tmp)
			return (free_env_list(env_list), NULL);
		env_list = append_env(env_list, tmp);
		i++;
	}
	return (env_list);
}


static t_env_list	*append_env(t_env_list *env_list, t_env_list *new_env_list)
{
	t_env_list	*curr;

	if (!env_list)
		return (new_env_list);
	curr = env_list;
	while (curr->next)
		curr = curr->next;
	curr->next = new_env_list;
	return (env_list);
}

t_env	*prepare_env_var(char *env_var)
{
	t_env	*env_elm;
	char	*name;
	char	*value;
	int		l;

	if (!env_var)
		return (NULL);
	env_elm = malloc(sizeof(t_env));
	if (!env_elm)
		return (NULL);
	l = 0;
	while (env_var[l] != '=' && env_var[l] != '\0')
		l++;
	name = strndup(env_var, l);
	if (!name)
		return (free(env_elm), NULL);
	value = ft_strdup(env_var + l + 1);
	if (!value)
		return (free(env_elm), free(name), NULL);
	env_elm->name = name;
	env_elm->value = value;
	return (env_elm);
}

static t_env_list	*new_env_list(char *env_var)
{
	t_env_list	*env_list;

	env_list = malloc(sizeof(t_env_list));
	if (!env_list)
		return (NULL);
	env_list->var = prepare_env_var(env_var);
	if (!env_list->var)
		return (free(env_list), NULL);
	return (env_list);
}

static void	free_env_var(t_env *env_var)
{
	if (!env_var)
		return ;
	free(env_var->name);
	free(env_var->value);
	free(env_var);
}
static void	free_env_list(t_env_list *list)
{
	t_env_list	*next;
	if (!list)
		return ;
	while (list)
	{
		next = list->next;
		free_env_var(list->var);
		free(list);
		list = next;
	}
}

/*
static void	print_env_list(t_env_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("[%d] %s = %s\n", i, list->var->name, list->var->value);
		list = list->next;
		i++;
	}
}

int	main(void)
{
	t_env_list	*list;

	list = env();
	print_env_list(list);
}
*/

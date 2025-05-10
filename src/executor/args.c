/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:24:18 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/03 14:28:29 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"

static int	args_count(t_cmd *cmd);
static char	*expand_var(t_executor *executor, t_word *arg);

char	**prepare_args(t_executor *executor, t_cmd *cmd)
{
	char		**args;
	int			buf_idx;
	int			count;
	t_word_list	*list;

	count = args_count(cmd);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	buf_idx = 0;
	args[buf_idx++] = expand_var(executor, cmd->name);
	if (!cmd->name)
		return (args);
	list = cmd->args;
	while (list)
	{
		args[buf_idx++] = expand_var(executor, list->word);
		list = list->next;
	}
	args[buf_idx] = NULL;
	return (args);
}

static int	args_count(t_cmd *cmd)
{
	int			i;
	t_word_list *list;

	i = 1;
	list = cmd->args;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

static char	*get_next_token(t_executor *executor, char *str, int *idx)
{
	int		start;
	int		var_start;
	char	*key;
	char	*value;
	char	*tmp;

	start = *idx;
	if (str[*idx] == '$')
	{
		(*idx)++;
		var_start = *idx;
		while (ft_isalnum(str[*idx]) || str[*idx] == '_')
			(*idx)++;
		tmp = ft_strndup(str + var_start, *idx - var_start);
		key = ft_strjoin(tmp, "=");
		value = get_env(executor->env, key);
		return (free(tmp), free(key), value);
	}
	while (str[*idx] && str[*idx] != '$')
		(*idx)++;
	return (ft_strndup(str + start, *idx - start));
}

static char	*expand_var(t_executor *executor, t_word *arg)
{
	char	*result;
	char	*token;
	char	*tmp;
	int		i;

	if (!arg)
		return (NULL);
	if (arg->flag != TOKEN_DQ_WORD)
		return (ft_strdup(arg->str));
	else if (!ft_strchr(arg->str, '$'))
		return (ft_strdup(arg->str));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (arg->str[i])
	{
		token = get_next_token(executor, arg->str, &i);
		if (!token)
			return (free(result), NULL);
		tmp = result;
		result = ft_strjoin(result, token);
		free(tmp);
		free(token);
		if (!result)
			return (NULL);
	}
	return (result);
}

/*
int	main()
{
	t_word	t;
	t_executor	executor;
	char	*str = "Hello $FNAME $LNAME, how are you $VERB.";
	executor.env = env();
	t.str = str;
	t.flag = TOKEN_SQ_WORD;
	char *ex_str = expand_var(&executor, &t);
	printf("str: %s - ex_str: %s\n", str, ex_str);
	free(ex_str);
	free_env_list(executor.env);

}
*/

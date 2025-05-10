/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 05:42:13 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/03 09:47:52 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../scanner/scanner.h"
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

typedef struct s_astnode	t_ast_node;

typedef enum e_node_type
{
	NODE_CMD = 1,
	NODE_SUBSHELL,
	NODE_PIPE,
	NODE_BACKGROUND,
	NODE_LIST,
	NODE_AND = TOKEN_AND_AND,
	NODE_OR = TOKEN_OR
}	t_node_type;

typedef struct s_word
{
	char	*str;
	int		flag;
}	t_word;

typedef struct s_word_list
{
	t_word				*word;
	struct s_word_list	*next;
}	t_word_list;

typedef enum e_redir_type
{
	REDIR_IN = TOKEN_REDIR_IN,
	REDIR_OUT = TOKEN_REDIR_OUT,
	APPEND_OUT = TOKEN_APPEND_OUT,
	HEREDOC = TOKEN_HEREDOC,
}	t_redir_type;

typedef struct s_redir_list
{
	t_redir_type		type;
	t_word				*filename;
	struct s_redir_list	*next;
}	t_redir_list;

typedef struct s_cmd
{
	t_word			*name;
	t_word_list		*args;
	t_redir_list	*redir;
}	t_cmd;

struct s_astnode
{
	t_node_type			type;
	t_redir_list		*redir;
	union
	{
		t_cmd			*cmd;
		struct
		{
			t_ast_node	*left;
			t_ast_node	*right;
		}s_pipe;
		t_ast_node		*subshell;
		struct
		{
			t_ast_node	*left;
			t_ast_node	*right;
		}				s_binary;
		struct
		{
			t_ast_node	*cmd;
		}				s_background;
		struct
		{
			t_ast_node	**commands;
			int			count;
			int			size;
		}				s_list;
	}u_content;
};

typedef struct s_error
{
	int			code;
	const char	*msg;
	const char	*ctx;
}	t_error;

typedef struct s_parser
{
	t_scanner	*scanner;
	t_token		curr;
	t_token		prev;
	t_ast_node	*ast;
	int			has_error;
	t_error		error;
}	t_parser;

/* ast.c */
t_ast_node		*create_ast_node(t_node_type type);
void			free_ast_node(t_ast_node *root);
void			print_ast(t_ast_node *root, const char *prefix, bool is_last);

/* word.c */
t_word			*parse_word(t_parser *parser);
void			free_word(t_word *word);
int				is_word(t_token_type type);

/* word_list */
t_word_list		*parse_word_list(t_word_list **list, t_parser *parser);
void			free_word_list(t_word_list *head);
int				word_list_to_arr(t_word_list *word_list, char **dest);

/* parser.c */
t_ast_node		*parse(const char *src, int *lstatus);
void			parser_advance(t_parser *parser);
int				parser_match(t_parser *parser, t_token_type type);
void			init_parser(t_parser *parser, t_scanner *scanner);

/* redir.c */
t_redir_list	*parse_redir(t_redir_list **list, t_parser *parser);
void			free_redir_list(t_redir_list *list);
int				is_redir(t_token_type type);

/* cmd.c */
t_ast_node		*parse_cmd(t_parser *parser);
void			free_cmd(t_cmd *cmd);
void			print_cmd(t_cmd *cmd);

/* error.c*/
void			make_error(t_parser *parser, const char *msg, int code);
void			print_error(t_parser *parser);

/* pipeline.c */
t_ast_node		*parse_pipeline(t_parser *parser);

/* logical.c */
t_ast_node		*parse_logical(t_parser *parser);

/* command.c */
t_ast_node		*parse_command(t_parser *parser);

/* list.c */
t_ast_node		*parse_list(t_parser *parser);
t_ast_node		*alloc_commands(t_ast_node *node);
void			free_node_list(t_ast_node *node);

/* subshell.c */
t_ast_node		*parse_subshell(t_parser *parser);

/* ast.c */
t_ast_node		*create_ast_node(t_node_type type);
void			free_ast_node(t_ast_node *node);

#endif /* PARSER_H */

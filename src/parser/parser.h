/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 05:42:13 by ybouryal          #+#    #+#             */
/*   Updated: 2025/04/20 16:29:30 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../scanner/scanner.h"
# include <stdio.h>
# include <string.h>

typedef struct s_astnode	t_ast_node;

typedef enum	e_node_type
{
	WORD,
	WORD_LIST,
	ASSIGNMENT,
	REDIRECTION,
	SIMPLE_COMMAND,
	SIMPLE_COMMAND_ELEMENT,
	REDIRECTION_LIST,
	COMMAND,
	SHELL_COMMAND,
	FOR_COMMAND,
	SELECT_COMMAND,
	CASE_COMMAND,
	FUNCTION_DEF,
	SUBSHELL,
	IF_COMMAND,
	GROUP_COMMAND,
	ELIF_CLAUSE,
	CASE_CLAUSE,
	PATTERN_LIST,
	CASE_CLAUSE_SEQUENCE,
	PATTERN,
	LIST,
	COMPOUND_LIST,
	PIPELINE_COMMAND,
	PIPELINE,
	PROGRAM
}	t_node_type;


typedef struct	s_word
{
	char	*word;
	int		flag;
}	t_word;

typedef struct	s_word_list
{
	t_word				*word;
	struct s_word_list	*next;
}	t_word_list;

typedef struct s_pipeline
{
	t_ast_node	*left;
	t_ast_node	*right;
}	t_pipeline;

typedef struct s_command
{
	union d{
		t_pipeline			*cmd;
	};
}	t_command;


typedef struct	s_program
{
	t_ast_node	*stmt;
}	t_program;

struct	s_astnode
{
	t_node_type	type;
	union node {
		t_program	*program;
	};
};

typedef struct	s_parser
{
	t_scanner	*scanner;
	t_token		curr;
	t_token		prev;
	t_ast_node	*ast;
}	t_parser;


typedef struct	s_redir_list
{

}	t_redir_list;

typedef struct	s_cmd
{
	t_word			*name;
	t_word_list		*args;
	t_redir_list	*redir;
}	t_cmd;


/* ast.c */
t_ast_node	*init_ast(void);

/* word.c */
t_word		*parse_word(t_parser *parser);
void		free_word(t_word *word);

/* word_list.c */
t_word_list	*parse_word_list(t_parser *parser);

/* parser.c */
t_ast_node	*parse(const char *src);
void		parser_advance(t_parser *parser);
int			parser_match(t_parser *parser, t_token_type type);
void		init_parser(t_parser *parser, t_scanner *scanner);

#endif /* PARSER_H */

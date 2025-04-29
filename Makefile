# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 14:28:19 by ybouryal          #+#    #+#              #
#    Updated: 2025/04/22 20:22:42 by ybouryal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN		:= $(shell tput -Txterm setaf 2)
BOLD		:= $(shell tput bold);
RESET		:= $(shell tput -Txterm sgr0)

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g
LDFLAGS		= -lreadline
RM			= rm -rf

SRCS_DIR	= src
BSRCS_DIR	= src_bonus
OBJS_DIR	= obj
BOBJS_DIR	= obj_bonus
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

# MFILES		= 
# BFILES		= 
# SRCS		= $(addprefix $(SRCS_DIR)/, $(MFILES))
# BSRCS		= $(addprefix $(BSRCS_DIR)/, $(BFILES))
# BOBJS		= $(patsubst $(BSRCS_DIR)/%.c, $(BOBJS_DIR)/%.o, $(BSRCS))

SRCS		= src/main.c src/prompt.c
PARSER		= $(wildcard $(SRCS_DIR)/parser/*.c)
SCANNER		= $(wildcard $(SRCS_DIR)/scanner/*.c)
EXECUTOR	= $(wildcard $(SRCS_DIR)/executor/*.c)

OBJS		= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

NAME		= minishell
BNAME		= minishell_bonus

all:		$(NAME)

# @$(CC) $(OBJS) -o $@ $(LDFLAGS)
# $(NAME):	$(OBJS) $(LIBFT)
$(NAME):	$(LIBFT) $(SRCS) $(PARSER) $(SCANNER) $(EXECUTOR)
			@$(CC) $(SRCS) $(PARSER) $(SCANNER) $(EXECUTOR) -o $@ $(CFLAGS) $(LDFLAGS) $(LIBFT)
			@echo "$(BOLD)$(GREEN)$(NAME) compiled Successfully$(RESET)"

$(OBJS_DIR)/%.o:		$(SRCS_DIR)/%.c $(SRCS_DIR)/parser/%.c $(SRCS_DIR)/scanner/%.c
			@mkdir -p $(OBJS_DIR)
			@mkdir -p $(OBJS_DIR)/parser
			@mkdir -p $(OBJS_DIR)/scanner
			@$(CC) $(CFLAGS) -c $< -o $@
			@echo "Compiling $(NAME) ..."

bonus:		$(BNAME)

$(BNAME):	$(BOBJS) $(LIBFT)
			@$(CC) $(BOBJS) -o $@ $(LDFLAGS)
			@echo "$(BOLD)$(GREEN)$(BNAME) compiled successfully$(RESET)"

$(BOBJS_DIR)/%.o:	$(BSRCS_DIR)/%.c
			@mkdir -p $(BOBJS_DIR)
			@$(CC) $(CFLAGS) -c $< -o $@
			@echo "Compiling $(BNAME) ..."

$(LIBFT):
			@$(MAKE) all bonus -C $(LIBFT_DIR)

clean:
			@$(RM) $(OBJS_DIR)
			@$(RM) $(BOBJS_DIR)
			@$(MAKE) clean -C $(LIBFT_DIR)
			@echo "Cleaning obj files."

fclean:	
			@echo "Cleaning all files."
			@$(MAKE) clean
			@$(RM) $(NAME)
			@$(RM) $(BNAME)
			@$(MAKE) fclean -C $(LIBFT_DIR)

re:
			@echo "Rebuild $(NAME)"
			@$(MAKE) fclean
			@$(MAKE) all

.PHONY: all clean fclean re bonus
.SECONDARY:	$(OBJS) $(BOBJS) $(LIBFT)

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 18:23:18 by anaraujo          #+#    #+#              #
#    Updated: 2023/06/13 22:19:53 by csilva-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
BONUS := 

CC := cc
CFLAGS := -Wall -Werror -Wextra -g

ifdef DEBUG
	CFLAGS += -fsanitize=address
endif

LIBFT := ./libft/libft.a

SRCS := srcs/main.c							srcs/initialize.c					\
		srcs/print.c						srcs/print2.c						\
		srcs/signals.c															\
		srcs/ast/ast.c						srcs/ast/ast_utils.c				\
		srcs/ast/ast_utils_2.c				srcs/ast/ast_utils_3.c				\
		srcs/ast/ast_utils_4.c				srcs/ast/call_ast.c					\
		srcs/ast/expand.c					srcs/ast/expand_utils.c				\
		srcs/builtins/ft_cd.c				srcs/builtins/ft_echo.c				\
		srcs/builtins/ft_env.c				srcs/builtins/ft_exit.c				\
		srcs/builtins/ft_export.c			srcs/builtins/ft_export_utils.c		\
		srcs/builtins/ft_export_utils2.c	srcs/builtins/ft_export_utils3.c	\
		srcs/builtins/ft_export_utils4.c	srcs/builtins/ft_export_utils5.c	\
		srcs/builtins/ft_pwd.c													\
		srcs/builtins/ft_unset.c			srcs/builtins/ft_unset_utils.c		\
		srcs/builtins/ft_unset_utils2.c											\
		srcs/error/error.c					srcs/error/error2.c					\
		srcs/error/free_all.c				srcs/error/free_all_aux.c			\
		srcs/exec/exec_builtins.c			srcs/exec/ft_exec.c					\
		srcs/exec/ft_exec_utils.c			srcs/exec/ft_exec_utils_2.c			\
		srcs/lexer/lexer.c					srcs/lexer/lexer_utils.c			\
		srcs/lexer/lexer_utils2.c			srcs/lexer/lexer_utils3.c			\
		srcs/lexer/lexer_utils4.c			srcs/lexer/lexer_utils5.c			\
		srcs/pipes/pipes.c					srcs/pipes/pipes_utils3.c			\
		srcs/pipes/pipes_utils.c			srcs/pipes/pipes_utils2.c			\
		srcs/pipes/pipes_fill_fds.c												\
		srcs/prompt/prompt.c				srcs/prompt/prompt_line.c			\
		srcs/redirects/redirects.c
									
		

SRCS_BONUS := 

OBJS := $(SRCS:.c=.o)

OBJS_BONUS := $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft
	echo "\033[1m LIBFT done \033[0m"

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -lm $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	echo "\033[1m $(NAME) ready \033[0m"

bonus: $(BONUS)

$(BONUS): $(OBJS_BONUS) $(LIBFT)
		$(CC) $(CFLAGS) -lm $(OBJS_BONUS) $(LIBFT) -o $(BONUS)
		echo "\033[1m $(BONUS) ready \033[0m"

clean:
		$(MAKE) clean -C ./libft
		rm -rf $(OBJS)
		rm -rf $(OBJS_BONUS)
		echo "OBJS deleted"

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -rf $(NAME)
		rm -rf $(BONUS)
		echo "$(NAME) deleted"
		echo "$(BONUS) deleted"

re: fclean all

.SILENT:

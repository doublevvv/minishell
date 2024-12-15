# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evlim <evlim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 08:37:40 by evlim             #+#    #+#              #
#    Updated: 2024/12/13 09:02:03 by evlim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = minishell.h

SOURCES = srcs/main.c	\
		srcs/libft/check.c	\
		srcs/libft/lst.c	\
		srcs/libft/ft_printf.c	\
		srcs/libft/ft_split.c	\
		srcs/libft/ft_str.c	\
		srcs/libft/ft_str2.c	\
		srcs/libft/ft_str3.c	\
		srcs/parsing/init.c	\
		srcs/parsing/prompt.c	\
		srcs/parsing/lst_to_array.c	\
		srcs/parsing/env_path.c	\
		srcs/parsing/path.c	\
		srcs/env/ft_env.c	\
		srcs/env/env_to_tab.c	\
		srcs/env/env_utils.c	\
		srcs/execution/exec.c	\
		srcs/execution/exec2.c	\
		srcs/execution/redirection.c	\
		srcs/builtin/ft_echo.c	\
		srcs/builtin/ft_exit.c	\
		srcs/builtin/ft_pwd.c	\
		srcs/builtin/ft_cd.c	\
		srcs/builtin/ft_export.c	\
		srcs/builtin/ft_unset.c	\
		srcs/expand/expand.c	\
		srcs/signal/signal.c	\
		srcs/free/free.c	\
		srcs/free/free2.c

SRCS = $(addprefix $(OBJ_DIR)/, $(SOURCES))

OBJ_DIR = objs

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3
#CFLAGS = -g3

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(OBJ_DIR)

re: fclean
	make all

.PHONY: all clean fclean re
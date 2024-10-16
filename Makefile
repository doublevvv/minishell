# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evlim <evlim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 08:37:40 by evlim             #+#    #+#              #
#    Updated: 2024/10/16 09:57:11 by evlim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = minishell.h

SOURCES = srcs/main.c	\
		srcs/parsing/prompt.c	\
		srcs/parsing/redirection.c	\
		srcs/libft/ft_split_pipe.c	\
		srcs/libft/ft_split_quote.c	\
		srcs/libft/check.c	\
		srcs/libft/lst.c

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
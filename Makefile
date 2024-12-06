# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 08:37:40 by evlim             #+#    #+#              #
#    Updated: 2024/12/06 09:23:55 by vlaggoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = minishell.h

SOURCES = srcs/main.c	\
		srcs/parsing/prompt.c	\
		srcs/libft/ft_split.c	\
		srcs/libft/utils.c ft_exit.c \
		srcs/libft/ft_strlen.c \
		ft_env.c srcs/libft/ft_strchr.c srcs/libft/ft_strncpy.c \
		srcs/libft/ft_memset.c utils_linked_list_env.c srcs/libft/ft_strnstr.c \
		srcs/libft/ft_strjoin.c ft_unset.c ft_export.c srcs/libft/ft_isalpha.c \
		srcs/libft/ft_isdigit.c srcs/libft/ft_calloc.c ft_echo.c ft_cd.c ft_pwd.c \
		srcs/libft/ft_strncmp.c expand.c srcs/libft/ft_isalnum.c srcs/libft/ft_memcpy.c \
		srcs/libft/ft_strdup.c
		

SRCS = $(addprefix $(OBJ_DIR)/, $(SOURCES))

OBJ_DIR = objs

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 
#-fsanitize=address
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
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 16:25:55 by vlaggoun          #+#    #+#              #
#    Updated: 2024/11/26 15:53:30 by vlaggoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Wextra -Werror
NAME	= libft.a
RM	= /bin/rm -f
HEADER = libft.h

SRCS	= ft_isascii.c ft_isprint.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
        ft_tolower.c ft_toupper.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
        ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
        ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_striteri.c \
        ft_memchr.c ft_memcmp.c ft_strdup.c ft_calloc.c ft_itoa.c \
        ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
        ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c ft_strcmp.c

BONUS_S	= ft_lstnew.c ft_lstadd_front.c ft_lstlast.c ft_lstadd_back.c \
	  ft_lstsize.c ft_lstdelone.c ft_lstclear.c 

OBJS	= $(SRCS:.c=.o)
OBJSbonus	= $(BONUS_S:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus:		$(OBJSbonus) $(OBJS)
	ar rcs $(NAME) $(OBJSbonus) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJSbonus)

fclean:	clean
	$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY:	all clean fclean re bonus

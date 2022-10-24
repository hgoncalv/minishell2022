# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/28 13:24:58 by mda-cruz          #+#    #+#              #
#    Updated: 2022/10/06 22:34:18 by mda-cruz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a
HEADER 		= libft.h
SRC 		= ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
		ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
		ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
		ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_memccpy.c \
		ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
		ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
		ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c
BONUS 		= ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
		ft_lstnew.c ft_lstsize.c
OBJ 		= ${SRC:.c=.o}
BONUS_OBJS	= $(BONUS:.c=.o)
FLAGS 		= -Wall -Wextra -Werror

all: ${NAME}

$(NAME): ${OBJ}
	ar -rs ${NAME} ${OBJ}

%.o: %.c 
	gcc ${FLAGS} -c -o $@ $<

bonus: ${NAME} ${BONUS} ${BONUS_OBJS}
	ar -rs ${NAME} ${OBJ} ${BONUS_OBJS}

clean:
	rm -f ${OBJ} ${BONUS_OBJS}

.PHONY: clean
fclean: clean
	rm -f ${NAME}

re: fclean all
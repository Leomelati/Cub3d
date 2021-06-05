# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/24 10:59:55 by lmartins          #+#    #+#              #
#    Updated: 2021/06/05 07:20:59 by lmartins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
ft_substr.c ft_tolower.c ft_toupper.c ft_lstadd_back.c ft_lstadd_front.c \
ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
ft_lstnew.c ft_lstsize.c ft_putnbr_uns_fd.c ft_putnbr_hex.c \
ft_putnbr_hex_lower.c ft_intlen.c ft_hexlen.c ft_itoa_uns.c ft_itoa_base.c \
get_next_line.c ft_swap.c ft_replace.c ft_strjoin_free.c ft_calloc_char.c \
ft_isspace.c ft_split_free.c

OBJ_FILES = $(FILES:.c=.o)

CC = gcc -Wall -Wextra -Werror
NAME = libft.a

INCLUDES = -I../include

RM = rm -rf

all:	$(NAME)

$(NAME): $(OBJ_FILES)
	@ar rcs $(NAME) $(OBJ_FILES)

clean:
	@$(RM) $(OBJ_FILES)

lclean: clean
	@$(RM) $(NAME)

fclean:	clean lclean
	
re:	fclean all

.c.o:
	@$(CC) -c $< -o $(<:.c=.o) $(INCLUDES)

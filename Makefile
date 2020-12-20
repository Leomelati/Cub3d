# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/24 10:59:55 by lmartins          #+#    #+#              #
#    Updated: 2020/12/20 08:08:56 by lmartins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = srcs/
SRC_FILES = main.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_FILES = $(SRC:.c=.o)

# CC = gcc -Wall -Wextra -Werror -fsanitize=address
CC = gcc

NAME = cub3D

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx_Linux.a

INCLUDES = -I./include -I./minilibx-linux
INCLUDE_LIBS = -L. $(LIBFT) -L. $(MLX) -lmlx -lXext -lX11

RM = rm -rf

all:	$(NAME)

$(NAME): $(OBJ_FILES)
	$(info Making libft)
	@make -C libft/
	$(info Making minilibx)
	@make -C minilibx-linux
	$(info Making cub3d)
	@$(CC) -o $(NAME) $(SRC) $(INCLUDES) $(INCLUDE_LIBS)
	
clean:
	@make -sC libft/ clean
	@make -sC minilibx-linux/ clean
	@$(RM) $(OBJ_FILES)

lclean: clean
	@make -sC libft/ lclean
	@$(RM) ./srcs/libft.a

fclean:	clean lclean
	@make -sC libft/ fclean
	@$(RM) $(NAME)
	
re:	fclean all

.c.o:
	@$(CC) -c $< -o $(<:.c=.o) $(INCLUDES)

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/24 10:59:55 by lmartins          #+#    #+#              #
#    Updated: 2020/12/20 09:06:14 by lmartins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Cub3d Infos

CUB_DIR = src/
CUB = $(CUB_DIR)/main.c

OBJ_FILES = $(CUB:.c=.o)

# Libft Infos
LIB_DIR = ./libft
LIB = $(LIB_DIR)/libft.a

# Minilibx Infos
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a

# Compiler Infos

# CC = gcc -Wall -Wextra -Werror -fsanitize=address
CC = gcc

INCLUDE = -I ./include -I $(LIB_DIR) -I $(MLX_DIR)
INCLUDE_FLAGS = -L $(LIB_DIR) -L $(MLX_DIR) -lmlx-Linux - lXext -lX11 -lm -lz

NAME = cub3D

# Rules flags

RM = rm -rf

# Rules

all:	$(NAME)

$(NAME): $(OBJ_FILES) $(LIB) $(MLX)
	@$(CC) $(INCLUDE_FLAGS) -o $(NAME) $(OBJ_FILES) $(LIB) $(MLX)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(MLX)
	$(MAKE) -C $(MLX_DIR)
	
clean:
	$(MAKE) -C libft/ clean
	$(MAKE) -C minilibx-linux/ clean
	$(RM) $(OBJ_FILES)

lclean: clean
	$(MAKE) -C libft/ lclean
	$(MAKE) -C minilibx-linux/ lclean

fclean:	clean lclean
	$(MAKE) -C libft/ fclean
	$(RM) $(NAME)
	
re:	fclean all

.c.o:
	@$(CC) -c $< -o $(<:.c=.o) $(INCLUDES)

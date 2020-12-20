# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/24 10:59:55 by lmartins          #+#    #+#              #
#    Updated: 2020/12/20 09:33:44 by lmartins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Cub3d Infos

CUB_DIR = ./src
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
INCLUDE_FLAGS = -L $(LIB_DIR) -lft -L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext

NAME = cub3D

# Rules flags

RM = rm -rf

# Rules

all:	$(NAME)

$(NAME): $(OBJ_FILES) $(LIB) $(MLX)
	@$(CC) $(OBJ_FILES) $(LIB) $(MLX) $(INCLUDE_FLAGS) -o $(NAME)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)
	
clean:
	$(MAKE) -C libft/ clean
	$(MAKE) -C minilibx-linux/ clean
	$(RM) $(OBJ_FILES)

lclean: clean
	$(MAKE) -C libft/ lclean
	$(MAKE) -C minilibx-linux/ lclean
	$(RM) $(NAME)

fclean:	clean lclean
	$(MAKE) -C libft/ fclean
	
re:	fclean all

.c.o:
	@$(CC) -c $< -o $(<:.c=.o) $(INCLUDE)

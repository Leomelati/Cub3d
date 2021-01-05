# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/24 10:59:55 by lmartins          #+#    #+#              #
#    Updated: 2021/01/05 06:43:45 by lmartins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Test Infos
TEST_FILES = src/main.c src/init.c src/key.c src/player.c src/free.c libft/ft_bzero.c libft/ft_memcpy.c libft/ft_calloc.c libft/ft_hexlen.c libft/ft_intlen.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa_base.c libft/ft_itoa_uns.c libft/ft_itoa.c libft/ft_memccpy.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putnbr_hex_lower.c libft/ft_putnbr_hex.c libft/ft_putnbr_uns_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_atoi.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strchr.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c libft/get_next_line.c minilibx-linux/mlx_screen_size.c minilibx-linux/mlx_destroy_window.c minilibx-linux/mlx_init.c minilibx-linux/mlx_new_window.c minilibx-linux/mlx_hook.c minilibx-linux/mlx_loop.c minilibx-linux/mlx_clear_window.c minilibx-linux/mlx_destroy_display.c minilibx-linux/mlx_destroy_image.c minilibx-linux/mlx_expose_hook.c minilibx-linux/mlx_flush_event.c minilibx-linux/mlx_get_color_value.c minilibx-linux/mlx_get_data_addr.c minilibx-linux/mlx_int_anti_resize_win.c minilibx-linux/mlx_int_do_nothing.c minilibx-linux/mlx_int_get_visual.c minilibx-linux/mlx_int_param_event.c minilibx-linux/mlx_int_set_win_event_mask.c minilibx-linux/mlx_int_str_to_wordtab.c minilibx-linux/mlx_int_wait_first_expose.c minilibx-linux/mlx_key_hook.c minilibx-linux/mlx_loop_hook.c minilibx-linux/mlx_mouse_hook.c minilibx-linux/mlx_mouse.c minilibx-linux/mlx_new_image.c minilibx-linux/mlx_pixel_put.c minilibx-linux/mlx_put_image_to_window.c minilibx-linux/mlx_rgb.c minilibx-linux/mlx_set_font.c minilibx-linux/mlx_string_put.c minilibx-linux/mlx_xpm.c
# minilibx-linux/mlx_lib_xpm.c minilibx-linux/mlx_screen_size.c minilibx-linux/mlx_ext_randr.c
TEST_FLAGS = -g


# Cub3d Infos

CUB_DIR = ./src
CUB = $(CUB_DIR)/main.c $(CUB_DIR)/free.c $(CUB_DIR)/init.c $(CUB_DIR)/key.c $(CUB_DIR)/player.c

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

test:
	@$(CC) $(TEST_FLAGS) $(TEST_FILES) $(INCLUDE) $(INCLUDE_FLAGS)

clean:
	$(MAKE) -C libft/ clean
	$(MAKE) -C minilibx-linux/ clean
	$(RM) $(OBJ_FILES)

lclean: clean
	@rm $(NAME)
	$(MAKE) -C libft/ lclean
	$(MAKE) -C minilibx-linux/ lclean

fclean:	clean lclean
	$(MAKE) -C libft/ fclean
	
re:	fclean all

.c.o:
	@$(CC) -c $< -o $(<:.c=.o) $(INCLUDE)

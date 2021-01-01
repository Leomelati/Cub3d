/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 10:11:40 by lmartins          #+#    #+#             */
/*   Updated: 2021/01/01 03:00:50 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** Includes
*/

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <math.h>

/*
** Struct
*/

typedef struct 	s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;
}				t_img;
typedef struct 	s_parameters
{
	void *mlx;
	void *win;
	int	width;
	int height;
	int floor_color;
	int ceilling_color;
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	char *sprite_texture;
	t_img	*img;
	int valid;

}				t_parameters;

typedef struct 	s_player
{
	int pos_x;
	int pos_y;
}				t_player;

/*
** Defines
*/

#define MISS -1
#define TRUE 1
#define FALSE 0
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

/*
** Cub3D Prototypes
*/

int		destroy_window(t_parameters *info);
void	define_resolution(t_parameters *info, char *readed);
char	*read_image_path(char *readed, t_parameters *info);
int		key_hook(int keycode, t_parameters *info, t_player *player, t_img *img);
void	read_infos(int fd, t_parameters *info);
void	start_infos(t_parameters *info, t_player *player);
void	ft_pixel_put(t_img *data, int x, int y, int color);
void	ft_free_img(t_parameters *info, t_img *img);
t_img	*ft_new_image(t_parameters *info, int width, int height, t_player *player);
int		ft_run(t_parameters *info, t_player *player, t_img *img);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 10:11:40 by lmartins          #+#    #+#             */
/*   Updated: 2021/01/03 08:51:15 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** Includes
*/

# include "libft.h"
# include "mlx.h"
# include <stdio.h> // Will be removed
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

typedef struct 	s_player
{
	double pos_x;
	double pos_y;
	double pdx;
	double pdy;
	double angle;

}				t_player;
typedef struct 	s_parameters
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	int			floor_color;
	int			ceilling_color;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*sprite_texture;
	t_img		*img;
	t_player	*player;
	int 		valid;

}				t_parameters;

/*
** Defines
*/

#define MISS -1
#define TRUE 1
#define FALSE 0
#define PI 3.1415926535
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

/*
** Cub3D Prototypes
*/

/*
** main.c
*/

void	draw2dMap(t_img	*img, t_parameters *info);
void	draw3dRays(t_img	*img, t_parameters *info);
void	draw_player(t_img	*img, t_parameters *info);
char	*read_image_path(char *readed, t_parameters *info);
int		key_hook(int keycode, t_parameters *info, t_img *img);
void	ft_pixel_put(t_img *data, int x, int y, int color);
t_img	*ft_new_image(t_parameters *info, int width, int height);
int		ft_run(t_parameters *info, t_img *img);

/*
** init.c
*/

void	define_resolution(t_parameters *info, char *readed);
t_player	*start_player();
void		read_infos(int fd, t_parameters *info);
void		start_infos(t_parameters *info);

/*
** free.c
*/

void	ft_free_img(t_parameters *info, t_img *img);
int		destroy_window(t_parameters *info);

#endif
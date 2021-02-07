/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 10:11:40 by lmartins          #+#    #+#             */
/*   Updated: 2021/02/07 10:20:12 by lmartins         ###   ########.fr       */
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

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct	s_player
{
	int		pos_x;
	int		pos_y;
	int		size;
	int		turn_direction;
	int		walk_direction;
	double	fov;
	double	rotation_angle;
	double	move_speed;
	double	rotation_speed;

}				t_player;

typedef struct	s_map
{
	char		**map;
	int			mapX;
	int			mapY;
	int			tam_altura;
	int			tam_largura;

}				t_map;

typedef struct	s_rays
{
	double	*rays;
	int		num_rays;

}				t_rays;
typedef struct	s_parameters
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
	t_map		*map;
	t_rays		*rays;
	int			valid;

}				t_parameters;

/*
** General Defines
*/

# define MISS -1
# define TRUE 1
# define FALSE 0
# define PI 3.14159265358979323846

/*
** Player Defines
*/

# define FOV_ANGLE 60
# define LEFT -1
# define RIGHT 1
# define BACK -1
# define FRONT 1

/*
** Rays Defines
*/

# define WALL_WIDTH 1
# define TRUE 1

/*
** Key Defines
*/

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEYPRESS_MASK 1
# define KEYRELEASE_MASK 10

/*
** Map Defines
*/

# define VALID_MAP_CHARS "012NSEW"
# define WALL '1'
# define PATH '0'
# define EMPTY ' '
# define PLAYER_START "NSEW"
# define NORTH 'N'
# define SOUTH 'S'
# define WEST 'W'
# define EAST 'E'

/*
** Cub3D Prototypes
*/

/*
** main.c
*/

char	*read_image_path(char *readed, t_parameters *info);
void	ft_pixel_put(t_img *data, int x, int y, int color);
t_img	*ft_new_image(t_parameters *info, int width, int height);
int		ft_run(t_parameters *info, t_img *img);

/*
** init.c
*/

void		define_resolution(t_parameters *info, char *readed);
t_map		*start_map();
t_player	*start_player(t_parameters *info);
int			is_map_line(char *readed);
void		read_infos(int fd, t_parameters *info);
void		start_infos(t_parameters *info);

/*
** line.c
*/

void	loop_ray_x(t_img *img, int *p1, int *array, int x, int y);
void	increment_x(t_img *img, int *p0, int *p1, int *array);
void	loop_ray_y(t_img *img, int *p1, int *array, int x, int y);
void	increment_y(t_img *img, int *p0, int *p1, int *array);
void	ft_draw_line(t_img *img, int *p0, int *p1, int color);

/*
** map.c
*/

int		ft_check_wall(int x, int y, t_parameters *info);
void	draw2dMap(t_img	*img, t_parameters *info);

/*
** key.c
*/

int		key_press(int keycode, t_parameters *info, t_img *img);
int		key_release(int keycode, t_parameters *info, t_img *img);

/*
** player.c
*/

void	player_start_position(t_parameters *info, t_player *player);
void	draw_player(t_img	*img, t_parameters *info);
void	ft_update_player(t_parameters *info);

/*
** rays.c
*/

void	draw_rays(t_img *img, t_parameters *info);
void	cast_rays(t_parameters *info);

/*
** free.c
*/

void	ft_free_img(t_parameters *info, t_img *img);
int		destroy_window(t_parameters *info);

#endif

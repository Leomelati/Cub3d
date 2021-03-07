/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 10:11:40 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/07 06:03:25 by lmartins         ###   ########.fr       */
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
# include <limits.h>

/*
** Struct
*/

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_player
{
	float		pos_x;
	float		pos_y;
	int			size;
	int			turn_direction;
	int			walk_direction;
	float		fov;
	float		rotation_angle;
	float		move_speed;
	float		rotation_speed;

}				t_player;

typedef struct	s_coordinates
{
	float		x;
	float		y;
}				t_coordinates;

typedef struct	s_map
{
	char		**map;
	int			map_x;
	int			map_y;
	int			num_rays;
}				t_map;

typedef struct	s_ray
{
	float		angle;
	float		collision_x;
	float		collision_y;
	float		distance;
	float		vertical_distance;
	float		horizontal_distance;
	float		vert_collision_x;
	float		vert_collision_y;
	float		horz_collision_x;
	float		horz_collision_y;
	int			vertical_hit;
	int			facing_down;
	int			facing_up;
	int			facing_right;
	int			facing_left;
}				t_ray;
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
	t_ray		**ray;
}				t_parameters;

/*
** General Defines
*/

# define MISS -1
# define TRUE 1
# define FALSE 0
# define PI 3.14159265358979323846

/*
** Error Defines
*/

# define ERROR_COLOR 0
# define ERROR_PATH 1
# define ERROR_ARGC 2
# define ERROR_SCREEN 3

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
# define KEY_ARROW_RIGHT 65363
# define KEY_ARROW_LEFT 65361
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
# define TILE_SIZE 64

/*
** Cub3D Prototypes
*/

/*
** main.c
*/

char			*read_image_path(char *readed, t_parameters *info);
void			ft_pixel_put(t_img *data, int x, int y, int color);
t_img			*ft_new_image(t_parameters *info, int width, int height);
int				ft_run(t_parameters *info, t_img *img);

/*
** auxiliar.c
*/

int				convert_color(char *readed, t_parameters *info);
float			calculate_distance(float x1, float y1, float x2, float y2);
float			normalize_angle(float ray_angle);

/*
** error.c
*/

void			define_error_message(int error_code, t_parameters *info);

/*
** parse.c
*/

void			check_parsed_info(t_parameters *info);
int				is_map_line(char *readed);
void			define_resolution(t_parameters *info, char *readed);
void			read_infos(int fd, t_parameters *info);

/*
** init.c
*/

t_ray			**start_rays(t_parameters *info);
t_map			*start_map();
char			**malloc_map(t_parameters *info, char *readed, int line);
void			start_infos(t_parameters *info);

/*
** line.c
*/

void			loop_ray_x(t_img *img, int *p1, int *array,
	t_coordinates loop);
void			increment_x(t_img *img, int *p0, int *p1, int *array);
void			loop_ray_y(t_img *img, int *p1, int *array,
	t_coordinates loop);
void			increment_y(t_img *img, int *p0, int *p1, int *array);
void			ft_draw_line(t_img *img, int *p0, int *p1, int color);

/*
** map.c
*/

int				ft_window_limit(float x, float y, t_parameters *info);
int				ft_check_wall(float x, float y, t_parameters *info);
void			draw2dmap(t_img	*img, t_parameters *info);

/*
** key.c
*/

int				key_press(int keycode, t_parameters *info, t_img *img);
int				key_release(int keycode, t_parameters *info, t_img *img);

/*
** player.c
*/

t_player		*start_player(t_parameters *info);
void			player_start_angle(char letter, t_player *player);
void			player_start_position(t_parameters *info, t_player *player);
void			draw_player(t_img	*img, t_parameters *info);
void		calculate_next_move(int keycode, float move_step,
	t_coordinates *next, t_parameters *info);
void			ft_update_player(int keycode, t_parameters *info);

/*
** rays.c
*/

void			compare_distance(t_parameters *info, int ray_id);
void			facing_position(t_parameters *info, t_ray *ray);
void			cast_rays(t_parameters *info);
void			cast_all_rays(t_img *img, t_parameters *info);

/*
** rays_intercept.c
*/

void			find_hoz_intersection(t_coordinates *check, t_coordinates *step,
	t_parameters *info, t_ray *ray);
void			horizontal_intersection(t_parameters *info, t_ray *ray);
void			find_vert_intersection(t_coordinates *check,
	t_coordinates *step, t_parameters *info, t_ray *ray);
void			vertical_intersection(t_parameters *info, t_ray *ray);

/*
** draw.c
*/

void			draw_3dwall(float wall_proj_height, int id,
	t_img *img, t_parameters *info);
void			wall_limits(t_img *img, t_parameters *info, float wall_height,
	int column_id);

/*
** free.c
*/

void			ft_free_img(t_parameters *info, t_img *img);
int				destroy_window(t_parameters *info);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 10:11:40 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/07 06:59:48 by lmartins         ###   ########.fr       */
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

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_player
{
	float		pos_x;
	float		pos_y;
	int			size;
	int			turn_dir;
	int			walk_direction;
	float		fov;
	float		rot_angle;
	float		move_speed;
	float		rot_speed;

}				t_player;

typedef struct s_coordinates
{
	float		x;
	float		y;
}				t_coordinates;

typedef struct s_sprite
{
	t_coordinates	pos;
	t_coordinates	map_pos;
	float			distance;
	float			angle;
	int				visible;
}				t_sprite;

typedef struct s_map
{
	char			**map;
	int				map_x;
	int				map_y;
	int				num_rays;
	int				n_sprites;
	t_coordinates	**sprites_map;
}					t_map;

typedef struct s_ray
{
	float		angle;
	float		collision_x;
	float		collision_y;
	float		distance;
	float		vert_distance;
	float		hor_distance;
	float		vert_coll_x;
	float		vert_coll_y;
	float		horz_coll_x;
	float		horz_coll_y;
	int			vertical_hit;
	int			facing_down;
	int			facing_up;
	int			facing_right;
	int			facing_left;
}				t_ray;
typedef struct s_parameters
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	int			floor_color;
	int			ceil_color;
	t_img		*north_tex;
	t_img		*south_tex;
	t_img		*west_tex;
	t_img		*east_tex;
	t_img		*sprite_tex;
	t_img		*img;
	t_player	*player;
	t_map		*map;
	t_ray		**ray;
	t_sprite	**sprites;
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

# define ERROR_PATH -1
# define ERROR_ARGC -2
# define ERROR_SCREEN -3
# define ERROR_PLAYER -4
# define ERROR_CHAR -5
# define ERROR_EXTENSION -6
# define ERROR_MLX -7
# define ERROR_COLOR -8
# define ERROR_INVALID_ARGUMENT -9
# define ERROR_INVALID_LINE -10
# define ERROR_INVALID_MAP -11
# define ERROR_TEXTURE -12

/*
** Player Defines
*/

# define FOV_ANGLE 60
# define LEFT -1
# define RIGHT 1
# define BACK -1
# define FRONT 1

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
# define PATH '0'
# define WALL '1'
# define SPRITE '2'
# define EMPTY ' '
# define PLAYER_START "NSEW"
# define NORTH 'N'
# define SOUTH 'S'
# define WEST 'W'
# define EAST 'E'
# define TILE_SIZE 81

/*
** Cub3D Prototypes
*/

/*
** main.c
*/

void			read_image_path(char *readed, t_parameters *info,
					t_img *texture);
void			ft_pixel_put(t_img *data, int x, int y, int color);
void			start_img(t_parameters *info);
int				ft_run(t_parameters *info);

/*
** auxiliar.c
*/

void			**allocate_dynamic(void **buffer, int size, int m);
int				check_char(t_map *map, int i, int j);
int				convert_color(char *readed, t_parameters *info);
float			calculate_distance(float x1, float y1, float x2, float y2);
float			normalize_angle(float ray_angle);

/*
** auxiliar2.c
*/

int				is_empty_line(char *line);
int				end_of_file(int fd, char **line);
t_coordinates	*create_point(float x, float y);
int				is_identifier(char *line);
int				read_info_if(char *readed, int *fd, int	*i, t_parameters *info);

/*
** error.c
*/

int				ft_error(t_parameters *info, int i);
int				ft_arg_error(int i);
void			check_starting_errors(int argc, char **argv);
void			check_extension(char *file);

/*
** init.c
*/

t_ray			**start_rays(t_parameters *info);
void			**allocate_new(void **buffer, int size, int line);
void			start_map(t_map *map);
void			start_infos(t_parameters *info);

/*
** parse.c
*/

void			define_resolution(t_parameters *info, char *readed);
int				assign_non_map_info(char *readed, t_parameters *info);
int				check_parsed_info(t_parameters *info);
int				parse_row_map(t_parameters *info, char *line, int row);
int				read_infos(char *file, t_parameters *info);

/*
** line.c
*/

void			loop_ray_x(t_img *img, t_coordinates p1, int *array,
					t_coordinates loop);
void			increment_x(t_img *img, t_coordinates p0, t_coordinates p1,
					int *array);
void			loop_ray_y(t_img *img, t_coordinates p1, int *array,
					t_coordinates loop);
void			increment_y(t_img *img, t_coordinates p0, t_coordinates p1,
					int *array);
void			ft_draw_line(t_img *img, t_coordinates p0, t_coordinates p1,
					int color);

/*
** map.c
*/

int				ft_window_limit(float x, float y, t_parameters *info);
int				ft_check_wall(float x, float y, t_parameters *info);
int				fill_rolls(t_parameters *info);
int				validate_map(t_map *map);
int				get_map_info(t_parameters *info, char *line, int *row,
					int *ismap);

/*
** key.c
*/

int				key_press(int keycode, t_parameters *info);
int				key_release(int keycode, t_parameters *info);

/*
** player.c
*/

void			start_player(t_player *player);
int				parse_initial_position(t_parameters *info, char c, int row,
					int column);
void			calculate_next_move(int keycode, float move_step,
					t_coordinates *next, t_parameters *info);
void			ft_update_player(int keycode, t_parameters *info);

/*
** rays.c
*/

void			compare_distance(t_parameters *info, int ray_id);
void			facing_position(t_parameters *info, t_ray *ray);
void			cast_rays(t_parameters *info, float dist_proj_plan);
void			cast_all_rays(t_parameters *info);

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
** wall.c
*/

void			draw_3dwall(float wall_proj_height, int id,
					t_img *img, t_parameters *info);
void			wall_limits(t_parameters *info,
					float wall_height, int column_id);

/*
** sprite.c
*/

t_sprite		**start_sprites(t_parameters *info);

/*
** error_messages.c
*/

char			*define_error_message(int error_code);

/*
** free.c
*/

int				close_program(void);
int				destroy_window(t_parameters *info);
int				clean_and_close(t_parameters *info);

/*
** ft_free_functions.c
*/

void			ft_free_sprites(t_parameters *info);
void			ft_free_rays(t_parameters *info);
void			ft_free_map(t_parameters *info);
void			ft_free_img(t_parameters *info, t_img *img);
void			ft_free_mlx(t_parameters *info);

#endif

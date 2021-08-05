/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 10:11:40 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/05 09:16:45 by lmartins         ###   ########.fr       */
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
	double		pos_x;
	double		pos_y;
	int			turn_dir;
	int			walk_direction;
	double		fov;
	double		rot_angle;
	double		move_speed;
	double		rot_speed;

}				t_player;

typedef struct s_coordinates
{
	double		x;
	double		y;
}				t_coordinates;

typedef struct s_sprite
{
	t_coordinates	*pos;
	int				height;
	int				width;
	double			distance;
	double			angle;
	double			angle_dif;
	
	double			init[2];
	double			end[2];
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
	double		angle;
	double		collision_x;
	double		collision_y;
	double		distance;
	double		vert_distance;
	double		hor_distance;
	double		vert_coll_x;
	double		vert_coll_y;
	double		horz_coll_x;
	double		horz_coll_y;
	int			vertical_hit;
	int			facing_down;
	int			facing_up;
	int			facing_right;
	int			facing_left;
	int			vert_content;
	int			horz_content;
	int			content;
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
# define HOR 0
# define VER 1
# define TOP 0
# define BOTTOM 1

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
# define TILE_SIZE 64

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
double			calculate_distance(double x0, double y0, double x1, double y1);
double			normalize_angle(double ray_angle);

/*
** auxiliar2.c
*/

int				is_empty_line(char *line);
int				end_of_file(int fd, char **line);
t_coordinates	*create_point(double x, double y);
int				is_identifier(char *line);
int				read_info_if(char *readed, int *fd, int	*i, t_parameters *info);
int				is_end_window(t_parameters *info, int x, int y);

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
void			start_sprites(t_parameters *info);

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

int				ft_window_limit(double x, double y, t_parameters *info);
int				ft_check_wall(double x, double y, t_parameters *info);
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
void			calculate_next_move(int keycode, double move_step,
					t_coordinates *next, t_parameters *info);
void			ft_update_player(int keycode, t_parameters *info);

/*
** rays.c
*/

void			compare_distance(t_parameters *info, int ray_id);
void			facing_position(t_parameters *info, t_ray *ray);
void			cast_rays(t_parameters *info, double dist_proj_plan);
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
void	define_intercept(t_parameters *info, t_ray *ray,
	t_coordinates	*intercept, int option);
void	define_step(t_parameters *info, t_ray *ray,
	t_coordinates	*step, int option);

/*
** wall.c
*/

int				get_color(t_img *img, int x, int y);
int				get_texture(t_parameters *info, int i, t_ray *ray, int *pixel);
void			draw_3dwall(double wall_proj_height, int id,
					t_img *img, t_parameters *info);
void			wall_limits(t_parameters *info,
					double wall_height, int column_id);

/*
** texture.c
*/

int	get_texture_north(t_parameters *info, int i, t_ray *ray, int *pixel);
int	get_texture_south(t_parameters *info, int i, t_ray *ray, int *pixel);
int	get_texture_east(t_parameters *info, int i, t_ray *ray, int *pixel);
int	get_texture_west(t_parameters *info, int i, t_ray *ray, int *pixel);
int	get_texture(t_parameters *info, int i, t_ray *ray, int *pixel);

/*
** sprite.c
*/

void	calculate_sprites_distances(t_parameters *info);
void	order_sprites_distance(t_parameters *info);
void	calculate_sprite_angles(t_parameters *info, t_sprite *sprite);
void	calculate_sprite_size(t_parameters *info, t_sprite *sprite);
void	draw_sprite(t_parameters *info, t_sprite *sprite, int x);
int		get_texture_color(t_img *tex, int x, int y);
void	cast_sprites(t_parameters *info);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);


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

void			ft_free_map_sprites(t_parameters *info);
void			ft_free_rays(t_parameters *info);
void			ft_free_map(t_parameters *info);
void			ft_free_img(t_parameters *info, t_img *img);
void			ft_free_mlx(t_parameters *info);

/*
** rays_sprites_intercept.c
*/

void	find_sprite_hoz_intersection(t_coordinates *check, t_coordinates *step,
	t_parameters *info, t_ray *ray);
void	horizontal_sprite_intersection(t_parameters *info, t_ray *ray);
void	find_sprite_vert_intersection(t_coordinates *check, t_coordinates *step,
	t_parameters *info, t_ray *ray);
void	vertical_sprite_intersection(t_parameters *info, t_ray *ray);

void	sprite_limits(t_parameters *info, double sprite_height, int column_id);


void	facing_sprite_position(t_parameters *info, t_ray *ray);
void	cast_all_sprite_rays(t_parameters *info);

int	ft_check_sprite(double x, double y, t_parameters *info);

#endif

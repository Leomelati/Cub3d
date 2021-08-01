/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 22:06:52 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/01 09:58:02 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_sprites_distances(t_parameters *info)
{
	int			i;

	i = 0;
	while (i < info->map->n_sprites)
	{
		info->sprites[i]->distance = calculate_distance(
			info->player->pos_x,
			info->player->pos_y,
			info->sprites[i]->pos->x,
			info->sprites[i]->pos->y);
		i++;
	}
}

void	order_sprites_distance(t_parameters *info)
{
	t_sprite	*temp;
	int			i;

	i = 0;
	while (i < info->map->n_sprites - 1)
	{
		if (info->sprites[i + 1]->distance > info->sprites[i]->distance)
		{
			temp = info->sprites[i];
			info->sprites[i] = info->sprites[i + 1];
			info->sprites[i + 1] = temp;
		}
		i++;
	}
}

void	calculate_sprite_angles(t_parameters *info, t_sprite *sprite)
{
	sprite->angle = atan2((sprite->pos->y - info->player->pos_y),
		(sprite->pos->x - info->player->pos_x));
	sprite->angle_dif = (info->player->rot_angle - sprite->angle);
	if (sprite->angle_dif < -1 * PI)
		sprite->angle_dif += 2 * PI;
	if (sprite->angle_dif > PI)
		sprite->angle_dif -= 2 * PI;
	sprite->angle_dif = fabs(sprite->angle_dif);
}

void	calculate_sprite_size(t_parameters *info, t_sprite *sprite)
{
	double	dist_proj_plan;
	int		x;

	x = 0;
	dist_proj_plan = (info->width / 2) / tan((info->player->fov / 2));
	sprite->distance *= (cos(sprite->angle_dif));
	if (sprite->angle_dif < info->player->fov / 2)
	{
		sprite->height = (TILE_SIZE * dist_proj_plan / sprite->distance);
		sprite->width = (sprite->height * info->sprite_tex-> width
		/ info->sprite_tex->height);
		x = tan(sprite->angle - info->player->rot_angle) * dist_proj_plan + (info->width / 2);
		draw_sprite(info, sprite, x);
	}
}

void	draw_sprite(t_parameters *info, t_sprite *sprite, int x)
{
	t_coordinates	tex;
	t_coordinates	in;
	t_coordinates	c;
	unsigned int	color;
	int				ray_sprite;

	in.x = x - sprite->width / 2;
	in.y = (info->height / 2) - (sprite->height / 2);
	c.x = 0;
	while (c.x < sprite->width)
	{
		c.y = 0;
		tex.x = c.x * info->sprite_tex->width / sprite->width;
		ray_sprite = (in.x + c.x);
		while (c.y < sprite->height)
		{
			tex.y = c.y * info->sprite_tex->height / sprite->height;
			if (!is_end_window(info, (in.x + c.x), (in.y + c.y)) &&
			sprite->distance < info->ray[(int)(ray_sprite)]->distance)
				(color = get_texture_color(info->sprite_tex, tex.x, tex.y)) ?
				my_mlx_pixel_put(info->img, in.x + c.x, in.y + c.y, color) : 0;
			c.y++;
		}
		c.x++;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst = data->addr + offset;
	*(unsigned int*)dst = color;
}

int			get_texture_color(t_img *tex, int x, int y)
{
	int		offset;

	offset = (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)(tex->addr + offset + 2) << 16 |
			*(unsigned int *)(tex->addr + offset + 1) << 8 |
			*(unsigned int *)(tex->addr + offset + 0) << 0);
}

void	cast_sprites(t_parameters *info)
{
	int		i;

	calculate_sprites_distances(info);
	order_sprites_distance(info);
	i = 0;
	while (i < info->map->n_sprites)
	{
		calculate_sprite_angles(info, info->sprites[i]);
		calculate_sprite_size(info, info->sprites[i]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 22:06:52 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/28 08:58:38 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_if_possible_draw(t_parameters *info, t_coordinates *tex,
	t_coordinates *in, t_coordinates *c)
{
	unsigned int	color;

	color = get_color(info->sprite_tex, tex->x, tex->y);
	if (color)
		ft_pixel_put(info->img, in->x + c->x, in->y + c->y, color);
}

void	draw_sprite(t_parameters *info, int i_sprite, int i)
{
	t_coordinates	tex;
	t_coordinates	in;
	t_coordinates	c;
	int				ray_sprite;

	in.x = i - info->sprites[i_sprite]->width / 2;
	in.y = (info->height / 2) - (info->sprites[i_sprite]->height / 2);
	c.x = 0;
	while (c.x < info->sprites[i_sprite]->width)
	{
		c.y = 0;
		tex.x = c.x * info->sprite_tex->width / info->sprites[i_sprite]->width;
		ray_sprite = in.x + c.x;
		while (c.y < info->sprites[i_sprite]->height)
		{
			tex.y = c.y * info->sprite_tex->height
				/ info->sprites[i_sprite]->height;
			if (!is_end_window(info, (in.x + c.x), (in.y + c.y))
				&& info->sprites[i_sprite]->distance
				< info->ray[(int)(ray_sprite)]->distance)
				check_if_possible_draw(info, &tex, &in, &c);
			c.y++;
		}
		c.x++;
	}
}

void	calculate_sprites_angle(t_parameters *info, double dist_plane,
		int i_sprite)
{
	int	i;

	i = 0;
	info->sprites[i_sprite]->angle = atan2(info->sprites[i_sprite]->pos->y
			- info->player->pos_y, info->sprites[i_sprite]->pos->x
			- info->player->pos_x);
	info->sprites[i]->angle_inc = info->player->rot_angle
		- info->sprites[i]->angle;
	if (info->sprites[i]->angle_inc < -1 * PI)
		info->sprites[i]->angle_inc += 2 * PI;
	if (info->sprites[i]->angle_inc > PI)
		info->sprites[i]->angle_inc -= 2 * PI;
	info->sprites[i]->angle_inc = fabs(info->sprites[i]->angle_inc);
	info->sprites[i]->distance *= (cos(info->sprites[i]->angle_inc));
	if (info->sprites[i]->angle_inc < info->player->fov / 2)
	{
		info->sprites[i]->height = (TILE_SIZE * dist_plane
				/ info->sprites[i]->distance);
		info->sprites[i]->width = (info->sprites[i]->height
				* info->sprite_tex->width / info->sprite_tex->height);
		i = tan(info->sprites[i]->angle - info->player->rot_angle)
			* dist_plane + (info->width / 2);
		draw_sprite(info, i_sprite, i);
	}
}

void	calculate_sprites_distances(t_parameters *info)
{
	int			i;

	i = 0;
	while (i < info->map->n_sprites)
	{
		info->sprites[i]->distance = calculate_distance(
				info->player->pos_x, info->player->pos_y,
				info->sprites[i]->pos->x, info->sprites[i]->pos->y);
		i++;
	}
}

void	cast_sprites(t_parameters *info)
{
	double	dist_plane;
	int		i_sprite;

	dist_plane = (info->width / 2) / (tan(info->player->fov / 2));
	calculate_sprites_distances(info);
	order_sprites_array(info);
	i_sprite = 0;
	while (i_sprite < info->map->n_sprites)
	{
		calculate_sprites_angle(info, dist_plane, i_sprite);
		i_sprite++;
	}
}

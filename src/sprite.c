/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 22:06:52 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/29 08:02:15 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	order_sprites_array(t_parameters *info)
{
	t_sprite	*tmp;
	int			i;

	i = 0;
	while (i < info->map->n_sprites - 1)
	{
		if (info->sprites[i]->distance < info->sprites[i + 1]->distance)
		{
			tmp = info->sprites[i];
			info->sprites[i] = info->sprites[i + 1];
			info->sprites[i + 1] = tmp;
		}
		i++;
	}
}

int		get_sprite_color(t_parameters *info, t_sprite *sprite, t_coordinates *pos)
{
	t_coordinates	offset;
	int				dist_top;
	int				diff;

	diff = (pos->x - sprite->init[0]);
	offset.x = diff * info->sprite_tex->width / sprite->width;
	if (offset.x < 0)
		offset.x *= -1;
	dist_top = pos->y + (sprite->height / 2) - (info->height / 2);
	offset.y = dist_top * ((double)info->sprite_tex->height / (double)sprite->height);
	return (*(unsigned int *)(info->sprite_tex->img + ((int)offset.y
		* info->sprite_tex->line_length + (int)offset.x
		* (info->sprite_tex->bits_per_pixel / 8))));
}

void	draw_sprite(t_parameters *info, t_sprite *sprite)
{
	t_coordinates	pos;
	int				color;

	pos.x = (int)sprite->init[0];
	while (pos.x < sprite->end[0])
	{
		pos.y = (int)sprite->init[1];
		while (pos.y < sprite->end[1])
		{
			if (!is_end_window(info, pos.x, pos.y))
			{
				if (sprite->distance < info->ray[(int)pos.x - 1]->distance)
				{
					color = get_color(info->sprite_tex, pos.x, pos.y);
					if (color)
						ft_pixel_put(info->img, pos.x, pos.y, color);
				}
			}
			pos.y++;
		}
		pos.x++;
	}
}

void	calculate_sprites_distances(t_parameters *info, t_sprite *sprite)
{
	double	dist_plane;

	dist_plane = (info->width / 2) / (tan(info->player->fov / 2));
	sprite->distance = calculate_distance(info->player->pos_x,
			info->player->pos_y, sprite->pos->x, sprite->pos->y);
	sprite->height = (info->sprite_tex->height / sprite->distance * dist_plane);
	sprite->height = (info->sprite_tex->height / sprite->distance) * dist_plane;
	sprite->width = (info->sprite_tex->width / sprite->distance) * dist_plane;
	sprite->init[1] = (info->height / 2) - (sprite->height / 2);
	if (sprite->init[1] < 0)
		sprite->init[1] = 0;
	sprite->end[1] = (info->height / 2) + (sprite->height / 2);
	if (sprite->end[1] > info->height)
		sprite->end[1] = info->height;
	sprite->angle = atan2(sprite->pos->y - info->player->pos_y, sprite->pos->x
			- info->player->pos_x) - info->player->rot_angle;
	sprite->init[0] = info->width + (tan(sprite->angle) * dist_plane);
	sprite->end[0] = sprite->init[0] + sprite->width;
}

void	cast_sprites(t_parameters *info)
{
	int		i;

	i = 0;
	while (i < info->map->n_sprites)
	{
		calculate_sprites_distances(info, info->sprites[i]);
		if (info->sprites[i]->angle > PI)
			info->sprites[i]->angle -= (2 * PI);
		if (info->sprites[i]->angle < -PI)
			info->sprites[i]->angle += (2 * PI);
		info->sprites[i]->angle = fabs(info->sprites[i]->angle);
		if (info->sprites[i]->angle < ((info->player->fov / 2) + 0.2))
			info->sprites[i]->visible = TRUE;
		else
			info->sprites[i]->visible = FALSE;
		i++;
	}
	order_sprites_array(info);
	i = 0;
	while (i < info->map->n_sprites)
	{
		if (info->sprites[i]->visible)
			draw_sprite(info, info->sprites[i]);
		i++;
	}
}

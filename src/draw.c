/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 04:39:43 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/07 04:43:40 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3dwall(float wall_proj_height, int id, t_img *img,
	t_parameters *info)
{
	int		line_start[2];
	int		line_end[2];

	line_start[0] = id + 1;
	line_start[1] = (info->width / 2) - (wall_proj_height / 2);
	line_start[1] = (line_start[1] > info->height) ?
		info->height : line_start[1];
	line_start[1] = (line_start[1] < 0) ? 0 : line_start[1];
	line_end[0] = id + 1;
	line_end[1] = line_start[1] + wall_proj_height;
	line_end[1] = (line_end[1] > info->height) ? info->height : line_end[1];
	line_end[1] = (line_end[1] < 0) ? 0 : line_end[1];
	if (info->ray[id]->vertical_hit)
		ft_draw_line(img, line_start, line_end, 0x00CA5F64);
	else
		ft_draw_line(img, line_start, line_end, 0x00ACF546);
}

void	wall_limits(t_img *img, t_parameters *info,
	float wall_height, int column_id)
{
	int		top_pixel;
	int		bottom_pixel;
	int		i;

	top_pixel = (info->height / 2) - (wall_height / 2);
	top_pixel = (top_pixel < 0) ? 0 : top_pixel;
	i = 0;
	while (i < top_pixel)
	{
		ft_pixel_put(img, column_id, i, info->ceilling_color);
		i++;
	}
	bottom_pixel = (info->height / 2) + (wall_height / 2);
	bottom_pixel = (bottom_pixel > info->height) ? info->height : bottom_pixel;
	i = bottom_pixel;
	while (i < info->height)
	{
		ft_pixel_put(img, column_id, i, info->floor_color);
		i++;
	}
}

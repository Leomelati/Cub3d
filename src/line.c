/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 09:30:22 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/07 07:09:07 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop_ray_x(t_img *img, t_coordinates p1, int *array, t_coordinates loop)
{
	int	distance;

	distance = array[1] - array[0];
	while (loop.x < p1.x)
	{
		if (distance < 0)
			distance += array[2];
		else
		{
			distance += array[3];
			if (loop.y < p1.y)
				loop.y += 1;
			else
				loop.y -= 1;
		}
		loop.x++;
		ft_pixel_put(img, loop.x, loop.y, array[4]);
	}
}

void	increment_x(t_img *img, t_coordinates p0, t_coordinates p1, int *array)
{
	t_coordinates	loop;

	if (p0.x < p1.x)
	{
		loop.x = p0.x;
		loop.y = p0.y;
	}
	else
	{
		ft_swap(&p0.x, &p1.x);
		ft_swap(&p0.y, &p1.y);
		loop.x = p0.x;
		loop.y = p0.y;
	}
	loop_ray_x(img, p1, array, loop);
}

void	loop_ray_y(t_img *img, t_coordinates p1, int *array, t_coordinates loop)
{
	int	distance;

	distance = array[0] - array[1];
	while (loop.y < p1.y)
	{
		if (distance < 0)
			distance += array[2];
		else
		{
			distance += array[3];
			if (loop.x < p1.x)
				loop.x += 1;
			else
				loop.x -= 1;
		}
		loop.y++;
		ft_pixel_put(img, loop.x, loop.y, array[4]);
	}
}

void	increment_y(t_img *img, t_coordinates p0, t_coordinates p1, int *array)
{
	t_coordinates	loop;

	if (p0.y < p1.y)
	{
		loop.x = p0.x;
		loop.y = p0.y;
	}
	else
	{
		ft_swap(&p0.x, &p1.x);
		ft_swap(&p0.y, &p1.y);
		loop.x = p0.x;
		loop.y = p0.y;
	}
	loop_ray_y(img, p1, array, loop);
}

void	ft_draw_line(t_img *img, t_coordinates p0, t_coordinates p1, int color)
{
	int		array[5];

	array[4] = color;
	array[0] = (p1.x - p0.x);
	if (array[0] > 0)
		array[0] *= 1;
	else
		array[0] *= -1;
	array[1] = (p1.y - p0.y);
	if (array[1] > 0)
		array[1] *= 1;
	else
		array[1] *= -1;
	if (array[0] >= array[1])
	{
		array[2] = array[1];
		array[3] = array[1] - array[0];
		increment_x(img, p0, p1, array);
	}
	else
	{
		array[2] = array[0];
		array[3] = array[0] - array[1];
		increment_y(img, p0, p1, array);
	}
}

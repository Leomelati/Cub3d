/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 09:30:22 by lmartins          #+#    #+#             */
/*   Updated: 2021/02/07 10:08:00 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop_ray_x(t_img *img, int *p1, int *array, int x, int y)
{
	int	distance;

	distance = array[1] - array[0];
	while (x <= p1[0])
	{
		if (distance < 0)
			distance += array[2];
		else
		{
			distance += array[3];
			y += (y < p1[1]) ? 1 : -1;
		}
		x++;
		ft_pixel_put(img, x, y, array[4]);
	}
}

void	increment_x(t_img *img, int *p0, int *p1, int *array)
{
	double x;
	double y;

	if (p0[0] < p1[0])
	{
		x = p0[0];
		y = p0[1];
	}
	else
	{
		ft_swap(&p0[0], &p1[0]);
		ft_swap(&p0[1], &p1[1]);
		x = p0[0];
		y = p0[1];
	}
	loop_ray_x(img, p1, array, x, y);
}

void	loop_ray_y(t_img *img, int *p1, int *array, int x, int y)
{
	int	distance;

	distance = array[0] - array[1];
	while (y <= p1[1])
	{
		if (distance < 0)
			distance += array[2];
		else
		{
			distance += array[3];
			x += (x < p1[0]) ? 1 : -1;
		}
		y++;
		ft_pixel_put(img, x, y, array[4]);
	}
}

void	increment_y(t_img *img, int *p0, int *p1, int *array)
{
	double x;
	double y;

	if (p0[1] < p1[1])
	{
		x = p0[0];
		y = p0[1];
	}
	else
	{
		ft_swap(&p0[0], &p1[0]);
		ft_swap(&p0[1], &p1[1]);
		x = p0[0];
		y = p0[1];
	}
	loop_ray_y(img, p1, array, x, y);
}

void	ft_draw_line(t_img *img, int *p0, int *p1, int color)
{
	int array[5];

	array[4] = color;
	array[0] = (p1[0] - p0[0]);
	array[0] *= (array[0] > 0) ? 1 : -1;
	array[1] = (p1[1] - p0[1]);
	array[1] *= (array[1] > 0) ? 1 : -1;
	if(array[0] >= array[1])
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
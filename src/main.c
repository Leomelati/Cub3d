/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 09:40:01 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/04 02:56:15 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*read_image_path(char *readed, t_parameters *info)
{
	t_img	*texture;
	char	**path;

	path = ft_split(readed, ' ');
	texture = ft_calloc(1, sizeof(t_img));
	texture->img = mlx_xpm_file_to_image(info->mlx, path[1], &texture->width, &texture->height);
	if (!texture->img)
	{
		free(path);
		path = NULL;
		ft_error(info, ERROR_PATH);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
	&texture->line_length, &texture->endian);
	return (texture);
}

void	ft_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_img	*ft_new_image(t_parameters *info, int width, int height)
{
	t_img	*img;

	if (!(img = ft_calloc(1, sizeof(t_img))))
		return (NULL);
	if (!(img->img = mlx_new_image(info->mlx, width, height)))
		return (NULL);
	if (!(img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian)))
		return (NULL);
	img->width = width;
	img->height = height;
	// draw2dmap(img, info);
	// draw_player(img, info);
	cast_all_rays(img, info);
	return (img);
}

int		ft_run(t_parameters *info, t_img *img)
{
	ft_free_img(info, info->img);
	info->img = ft_new_image(info, info->width, info->height);
	mlx_put_image_to_window(info->mlx, info->win, info->img->img, 0, 0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_parameters	info;
	t_img			img;


	check_starting_errors(argc, argv);
	start_infos(&info);
	//if (!read_infos(argv[1], &info))
	//	return (0);
	//info.ray = start_rays(&info);
	info.width = 500;
	info.height = 500;
	info.win = mlx_new_window(info.mlx, info.width, info.height, "cub3D");
	//ft_run(&info, &img);
	mlx_hook(info.win, 33, 0, clean_and_close, &info);
	//mlx_hook(info.win, KEY_PRESS, KEYPRESS_MASK, key_press, &info);
	//mlx_hook(info.win, KEY_RELEASE, KEYRELEASE_MASK, key_release, &info);
	mlx_loop(info.mlx);
	return (0);
}

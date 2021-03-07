/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 09:40:01 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/07 01:16:13 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*read_image_path(char *readed, t_parameters *info)
{
	int		img_width;
	int		img_height;
	void	*image;

	readed = &readed[3];
	image = mlx_xpm_file_to_image(info->mlx, readed, &img_width, &img_height);
	if (image == NULL)
		define_error_message(ERROR_PATH, info);
	return(image);
}

void	ft_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;
	
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_img	*ft_new_image(t_parameters *info, int width, int height)
{
	t_img	*img;
	
	if (!(img = malloc(sizeof(t_img))))
		return (NULL);
	if (!(img->img = mlx_new_image(info->mlx, width, height)))
		return (NULL);
	if (!(img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian)))
		return (NULL);
	img->width = width;
	img->height = height;
	// draw2dMap(img, info);
	// draw_player(img, info);
	draw_rays(img, info);
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

	start_infos(&info);
	info.mlx = mlx_init();
	if (argc != 2)
		define_error_message(ERROR_ARGC, &info);
	read_infos(open(argv[1], O_RDONLY), &info);
	info.win = mlx_new_window(info.mlx, info.width, info.height, "cub3D");
	ft_run(&info, &img);
	mlx_hook(info.win, 33, 0, destroy_window, &info);
	mlx_hook(info.win, KEY_PRESS, KEYPRESS_MASK, key_press, &info);
	mlx_hook(info.win, KEY_RELEASE, KEYRELEASE_MASK, key_release, &info);
	mlx_loop(info.mlx);
	return (0);
}

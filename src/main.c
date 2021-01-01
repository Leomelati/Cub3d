/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 09:40:01 by lmartins          #+#    #+#             */
/*   Updated: 2021/01/01 22:50:10 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw2dMap(t_img	*img, t_parameters *info)
{
	// WILL BE REMOVED
	int mapX = 8;
	int mapY = 1;
	int mapS = 64;
	int map[1][8] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1}
		// {1, 0, 1, 0, 0, 0, 0, 1},
		// {1, 0, 1, 0, 0, 0, 0, 1},
		// {1, 0, 1, 0, 0, 0, 0, 1},
		// {1, 0, 0, 0, 0, 0, 0, 1},
		// {1, 0, 0, 0, 0, 1, 0, 1},
		// {1, 0, 0, 0, 0, 0, 0, 1},
		// {1, 1, 1, 1, 1, 1, 1, 1}
	};

	int tam_altura = info->height / mapY;
	int tam_largura = info->width / mapX;
}

char	*read_image_path(char *readed, t_parameters *info) // Fix this later
{
	int		img_width;
	int		img_height;
	void	*image;

	// if (image != NULL)
		// info->valid = FALSE;
	readed = &readed[3];
	// printf("Readed:%s\n", readed);
	image = mlx_xpm_file_to_image(info->mlx, readed, &img_width, &img_height);
	// if (image == NULL)
		// info->valid = FALSE;
	// printf("Path: %p\n", image);
	return(image);
}

int		key_hook(int keycode, t_parameters *info, t_img *img)
{
	if (keycode == KEY_ESC)
		destroy_window(info);
	else if (keycode == KEY_A)
	{
		info->player->pos_x -= 5;
		ft_run(info, img);
	}
	else if (keycode == KEY_D)
	{
		info->player->pos_x += 5;
		ft_run(info, img);
	}
	else if (keycode == KEY_W)
	{
		info->player->pos_y -= 5;
		ft_run(info, img);
	}
	else if (keycode == KEY_S)
	{
		info->player->pos_y += 5;
		ft_run(info, img);
	}
	return (1);
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
	draw2dMap(img, info);
	for (int i = 0; i <= 10; i++) // WILL BE REMOVED
		for (int j = 0; j <= 10; j++) // WILL BE REMOVED
			ft_pixel_put(img, info->player->pos_x + i, info->player->pos_y + j, 0x00FF0000);
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
	read_infos(open(argv[1], O_RDONLY), &info);
	if (info.valid == TRUE)
	{
		info.win = mlx_new_window(info.mlx, info.width, info.height, "cub3D");
		ft_run(&info, &img);
		mlx_hook(info.win, 2, 1L << 0, key_hook, &info);
		mlx_hook(info.win, 33, 0, destroy_window, &info);
		mlx_loop(info.mlx);
	}
	return (0);
}

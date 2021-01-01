/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 09:40:01 by lmartins          #+#    #+#             */
/*   Updated: 2021/01/01 06:48:09 by lmartins         ###   ########.fr       */
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

	for (int y = 0; y < mapY; y++) // WILL BE REMOVED
		for (int x = 0; x < mapX; x++) // WILL BE REMOVED
		{
			if (map[y][x] == 1) // WILL BE REMOVED
				for (int i = 0; i <= tam_altura; i++)
					for (int j = 0; j <= tam_largura; j++)
					{
						printf("Tam_altura:%d\n", tam_altura);
						printf("Tam_largura:%d\n", tam_largura);
						printf("Pintando Pixel x:%d\n", i);
						printf("Pintando Pixel y:%d\n", j);
						ft_pixel_put(img, i, j, 0x00FF0000);
					}
		}
}

int		destroy_window(t_parameters *info)
{
	ft_free_img(info, info->img);
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
	return (0);
}

void	define_resolution(t_parameters *info, char *readed)
{
	char	**string;
	int		x;
	int		y;
	int		elements;

	if ((info->width != MISS) || (info->height != MISS))
		info->valid = FALSE;
	mlx_get_screen_size(info->mlx, &x, &y);
	string = ft_split(readed, ' ');
	elements = 0;
	while (string[elements])
		elements++;
	if (elements == 3)
	{
		info->width = (ft_atoi(string[1]) > x) ? x : ft_atoi(string[1]);
		info->height = (ft_atoi(string[2]) > y) ? y : ft_atoi(string[2]);
	}
	else
		info->valid = FALSE;
	free(string);
}

char	*read_image_path(char *readed, t_parameters *info)
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

int		key_hook(int keycode, t_parameters *info, t_player *player, t_img *img)
{
	// printf("%d\n", keycode);
	if (keycode == KEY_ESC)
		destroy_window(info);
	else if (keycode == KEY_A)
	{
		ft_run(info, player, img);
		player->pos_x -= 5;
	}
	else if (keycode == KEY_D)
	{
		ft_run(info, player, img);
		player->pos_x += 5;
	}
	else if (keycode == KEY_W)
	{
		ft_run(info, player, img);
		player->pos_y -= 5;
	}
	else if (keycode == KEY_S)
	{
		ft_run(info, player, img);
		player->pos_y += 5;
	}
	return (1);
}

void	read_infos(int fd, t_parameters *info)
{
	char *readed;

	while ((info->valid == TRUE) && (get_next_line(fd, &readed) == 1))
	{
		if (readed[0] == 'R')
			define_resolution(info, readed);
		else if (readed[0] == 'N' && readed[1] == 'O' && readed[2] == ' ')
			info->north_texture = read_image_path(readed, info);
	}
	free(readed);
}

void	start_infos(t_parameters *info, t_player *player)
{
	info->mlx = NULL;
	info->win = NULL;
	info->width = MISS;
	info->height = MISS;
	info->floor_color = MISS;
	info->ceilling_color = MISS;
	info->north_texture = NULL;
	info->south_texture = NULL;
	info->west_texture = NULL;
	info->east_texture = NULL;
	info->sprite_texture = NULL;
	info->img = NULL;
	info->valid = TRUE;

	player->pos_x = 200;
	player->pos_y = 300;
}

void	ft_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;
	
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_free_img(t_parameters *info, t_img *img)
{
	if (img)
	{
		mlx_destroy_image(info->mlx, img->img);
		free(img);
		img = NULL;
	}
}

t_img	*ft_new_image(t_parameters *info, int width, int height, t_player *player)
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
			ft_pixel_put(img, player->pos_x + i, player->pos_y + j, 0x00FF0000);
	return (img); 
}

int		ft_run(t_parameters *info, t_player *player, t_img *img)
{
	ft_free_img(info, info->img);
	info->img = ft_new_image(info, info->width, info->height, player);
	mlx_put_image_to_window(info->mlx, info->win, info->img->img, 0, 0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_parameters	info;
	t_player		player;
	t_img			img;

	start_infos(&info, &player);
	info.mlx = mlx_init();
	read_infos(open(argv[1], O_RDONLY), &info);
	if (info.valid == TRUE)
	{
		info.win = mlx_new_window(info.mlx, info.width, info.height, "cub3D");
		mlx_hook(info.win, 2, 1L << 0, key_hook, &info);
		mlx_hook(info.win, 33, 0, destroy_window, &info);
		mlx_loop(info.mlx);
	}
	return (0);
}

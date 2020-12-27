/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 09:40:01 by lmartins          #+#    #+#             */
/*   Updated: 2020/12/27 03:27:17 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		destroy_window(t_parameters *info)
{
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
	printf("Readed:%s\n", readed);
	image = mlx_xpm_file_to_image(info->mlx, readed, &img_width, &img_height);
	// if (image == NULL)
		// info->valid = FALSE;
	printf("Path: %p\n", image);
	return(image);
}

int		key_hook(int keycode, t_parameters *info)
{
	if (keycode == key_ESC)
		destroy_window(info);
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
}

void	start_infos(t_parameters *info)
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
	info->valid = TRUE;
}

int		main(int argc, char **argv)
{
	t_parameters	info;

	start_infos(&info);
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

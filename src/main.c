/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 09:40:01 by lmartins          #+#    #+#             */
/*   Updated: 2020/12/21 07:41:44 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	define_resolution(t_parameters *info, char *readed)
{
	char	**string;

	if (readed[0] = 'R')
	{
		string = ft_split(readed, ' ');
		info->width = ft_atoi(string[1]);
		info->height = ft_atoi(string[2]);
	}
}

int		key_hook(int keycode, t_parameters *info)
{
	printf("%i\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(info->mlx, info->window);
		exit(0);
	}
}

int		main(int argc, char **argv)
{
	char 			*readed;
	t_parameters	info;

	get_next_line(open(argv[1], O_RDONLY), &readed);
	define_resolution(&info, readed);
	info.mlx = mlx_init();
	info.window = mlx_new_window(info.mlx, info.width, info.height, "cub3D");
	mlx_key_hook(info.window, key_hook, &info);
	// mlx_hook(info.window, 2, 1L<<0, key_hook, &info);
	mlx_loop(info.mlx);
	return (0);	
}
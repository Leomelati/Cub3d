/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 09:40:01 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/08 09:51:27 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_parsed_status(t_parameters *info, char parsed)
{
	if (parsed == NORTH)
		info->parsed->north_tex = TRUE;
	else if (parsed == SOUTH)
		info->parsed->south_tex = TRUE;
	else if (parsed == WEST)
		info->parsed->west_tex = TRUE;
	else if (parsed == EAST)
		info->parsed->east_tex = TRUE;
}

void	read_image_path(char *readed, t_parameters *info, t_img *texture,
	char parsed)
{
	char	**path;

	path = ft_split(readed, ' ');
	texture->img = mlx_xpm_file_to_image(info->mlx,
			path[1], &texture->width, &texture->height);
	if (!texture->img)
	{
		ft_split_free(path);
		ft_error(info, ERROR_PATH);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	ft_split_free(path);
	change_parsed_status(info, parsed);
}

void	start_img(t_parameters *info)
{
	info->img->img = mlx_new_image(info->mlx, info->width, info->height);
	info->img->addr = mlx_get_data_addr(info->img->img,
			&info->img->bits_per_pixel, &info->img->line_length,
			&info->img->endian);
	info->img->width = info->width;
	info->img->height = info->height;
	info->parsed->img = TRUE;
}	

int	ft_run(t_parameters *info)
{
	cast_all_rays(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img->img, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_parameters	info;

	check_starting_errors(argc, argv);
	start_infos(&info);
	if (!read_infos(argv[1], &info))
		return (0);
	info.win = mlx_new_window(info.mlx, info.width, info.height, "cub3D");
	info.parsed->win = TRUE;
	ft_run(&info);
	mlx_hook(info.win, 33, 0, clean_and_close, &info);
	mlx_hook(info.win, KEY_PRESS, KEYPRESS_MASK, key_press, &info);
	mlx_loop_hook(info.mlx, ft_run, &info);
	mlx_loop(info.mlx);
	return (0);
}

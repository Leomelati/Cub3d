/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 02:36:48 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/08 09:43:34 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(t_parameters *info, int i)
{
	destroy_window(info);
	ft_putendl_fd(define_error_message(i), 1);
	return (close_program());
}

int	ft_arg_error(int i)
{
	ft_putendl_fd(define_error_message(i), 1);
	return (close_program());
}

void	check_starting_errors(int argc, char **argv)
{
	char	*extension;
	int		len;
	int		i;

	if (argc != 2)
		ft_arg_error(ERROR_ARGC);
	len = ft_strlen(argv[1]);
	i = len - 4;
	if (i < 4)
		ft_arg_error(ERROR_EXTENSION);
	extension = ft_strdup(&argv[1][i]);
	if (ft_strncmp(extension, ".cub", 5))
		ft_arg_error(ERROR_EXTENSION);
	free(extension);
}

char	*define_error_message(int error_code)
{
	if (error_code == ERROR_COLOR)
		return ("Error\nError message: Invalid color code.");
	else if (error_code == ERROR_PATH)
		return ("Error\nError message: Invalid texture path.");
	else if (error_code == ERROR_ARGC)
		return ("Error\nError message: Invalid argument.");
	else if (error_code == ERROR_SCREEN)
		return ("Error\nError message: Invalid resolution.");
	else if (error_code == ERROR_PLAYER)
		return ("Error\nError message: Invalid player position.");
	else if (error_code == ERROR_CHAR)
		return ("Error\nError message: Invalid map char.");
	else if (error_code == ERROR_EXTENSION)
		return ("Error\nError message: Invalid file format.");
	else if (error_code == ERROR_MLX)
		return ("Error\nError message: Mlx error.");
	else if (error_code == ERROR_INVALID_LINE)
		return ("Error\nError message: Invalid line.");
	else if (error_code == ERROR_INVALID_MAP)
		return ("Error\nError message: Invalid map.");
	else if (error_code == ERROR_INVALID_MAP)
		return ("Error\nError message: Could not load texture.");
	return (NULL);
}

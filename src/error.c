/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 02:36:48 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/06 07:59:23 by lmartins         ###   ########.fr       */
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

int	ft_path_error(t_parameters *info)
{
	ft_error(info, ERROR_TEXTURE);
	mlx_destroy_window(info->mlx, info->win);
	return (close_program());
}

void	check_starting_errors(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		ft_arg_error(ERROR_ARGC);
	else if (argc == 3 && ft_memcmp(argv[2], "--save", 6))
		ft_arg_error(ERROR_INVALID_ARGUMENT);
	check_extension(argv[1]);
}

void	check_extension(char *file)
{
	char	*extension;
	int		len;
	int		i;

	len = ft_strlen(file);
	i = len - 4;
	if (i < 4)
		ft_arg_error(ERROR_EXTENSION);
	extension = ft_strdup(&file[i]);
	if (ft_strncmp(extension, ".cub", 5))
		ft_arg_error(ERROR_EXTENSION);
	free(extension);
}

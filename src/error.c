/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 02:36:48 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/07 08:56:53 by lmartins         ###   ########.fr       */
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

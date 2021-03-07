/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 02:36:48 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/07 01:22:56 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	define_error_message(int error_code, t_parameters *info)
{
	if (error_code == ERROR_COLOR)
		ft_putendl_fd("Error: Invalid color code.", 1);
	else if (error_code == ERROR_PATH)
		ft_putendl_fd("Error: Invalid texture path.", 1);
	else if (error_code == ERROR_ARGC)
		ft_putendl_fd("Error: Invalid number of arguments.", 1);
	else if (error_code == ERROR_SCREEN)
		ft_putendl_fd("Error: Invalid resolution.", 1);
	destroy_window(info);
}
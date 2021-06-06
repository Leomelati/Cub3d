/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 07:59:04 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/06 08:02:54 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*define_error_message(int error_code)
{
	if (error_code == ERROR_COLOR)
		return ("Error: Invalid color code.");
	else if (error_code == ERROR_PATH)
		return ("Error: Invalid texture path.");
	else if (error_code == ERROR_ARGC)
		return ("Error: Invalid number of arguments.");
	else if (error_code == ERROR_SCREEN)
		return ("Error: Invalid resolution.");
	else if (error_code == ERROR_PLAYER)
		return ("Error: More than one or invalid player player position.");
	else if (error_code == ERROR_CHAR)
		return ("Error: Invalid map char.");
	else if (error_code == ERROR_EXTENSION)
		return ("Error: Invalid file format.");
	else if (error_code == ERROR_MLX)
		return ("Error: Mlx error.");
	else if (error_code == ERROR_INVALID_ARGUMENT)
		return ("Error: Invalid argument.");
	else if (error_code == ERROR_INVALID_LINE)
		return ("Error: Invalid line.");
	else if (error_code == ERROR_INVALID_MAP)
		return ("Error: Invalid map.");
	else if (error_code == ERROR_INVALID_MAP)
		return ("Error: Could not load texture.");
	return (NULL);
}

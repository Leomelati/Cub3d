/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 02:36:48 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/06 08:26:33 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	define_error_message(int error_code, t_parameters *info)
{
	if (error_code == 0)
		ft_putendl_fd("Error: Invalid color code.", 1);
	destroy_window(info);
}
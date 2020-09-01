/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 09:40:01 by lmartins          #+#    #+#             */
/*   Updated: 2020/09/01 09:04:41 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	void * mlx;
	mlx = mlx_init();
	mlx_new_window(mlx, 500, 500, "cub3D");
	mlx_loop(mlx);
	return (0);	
}
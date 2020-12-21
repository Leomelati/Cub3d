/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 10:11:40 by lmartins          #+#    #+#             */
/*   Updated: 2020/12/21 15:28:18 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** Includes
*/

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <math.h>

/*
** Struct
*/

typedef struct 	s_parameters
{
	void *mlx;
	void *window;
	int	width;
	int height;
	int floor_color;
	int ceilling_color;
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	char *sprite_texture;

}				t_parameters;

/*
** Defines
*/

#define key_ESC 65307
#define X_window_button 1321069248

#endif
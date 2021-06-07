/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 22:06:52 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/07 06:52:02 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	**start_sprites(t_parameters *info)
{
	t_sprite	**array;
	int			i;

	array = malloc(info->map->n_sprites * sizeof(t_ray *));
	if (!(array))
		return (NULL);
	i = 0;
	while (i <= info->map->n_sprites)
	{
		array[i] = calloc(1, sizeof(t_ray));
		i++;
	}
	return (array);
}

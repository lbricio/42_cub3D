/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbricio- <lbricio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:43:51 by lbricio-          #+#    #+#             */
/*   Updated: 2022/01/24 21:43:54 by lbricio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_floor(t_data *data)
{
	int		i;
	int		j;
	int		color;

	color = create_trgb(0, data->map.color_floor[0], \
		data->map.color_floor[1], data->map.color_floor[2]);
	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		j = SCREEN_HEIGHT / 2 - 1;
		while (++j < SCREEN_HEIGHT)
			my_mlx_pixel_put(data, i, j, color);
	}
}

void	draw_ceiling(t_data *data)
{
	int		i;
	int		j;
	int		color;

	color = create_trgb(0, data->map.color_ceiling[0], \
		data->map.color_ceiling[1], data->map.color_ceiling[2]);
	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		j = -1;
		while (++j < SCREEN_HEIGHT / 2)
			my_mlx_pixel_put(data, i, j, color);
	}
}

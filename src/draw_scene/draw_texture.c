/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbricio- <lbricio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:44:09 by lbricio-          #+#    #+#             */
/*   Updated: 2022/03/03 17:37:42 by lbricio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	aux_dda(t_data *data, t_rc *rc)
{
	rc->side_dist_x += rc->delta_dist_x;
	rc->map_x += rc->step_x;
	rc->side = 0;
	if (data->world_map[rc->map_x][rc->map_y] > 0)
	{
		rc->hit = 1;
		if (rc->map_x > data->pos_x)
			rc->tex_num = 0;
		else
			rc->tex_num = 2;
	}
}

void	perform_dda(t_data *data, t_rc *rc)
{
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
			aux_dda(data, rc);
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
			if (data->world_map[rc->map_x][rc->map_y] > 0)
			{
				rc->hit = 1;
				if (rc->map_y > data->pos_y)
					rc->tex_num = 3;
				else
					rc->tex_num = 1;
			}
		}
	}
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
	else
		rc->perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);
}

void	calc_texturing(t_data *data, t_rc *rc)
{
	rc->line_height = ((int)(SCREEN_HEIGHT / rc->perp_wall_dist)) * 2;
	rc->draw_start = -rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->draw_end >= SCREEN_HEIGHT)
		rc->draw_end = SCREEN_HEIGHT - 1;
	if (rc->side == 0)
		rc->wall_x = data->pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wall_x = data->pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	rc->wall_x -= floor((rc->wall_x));
	rc->tex_x = (int)(rc->wall_x * (double)(TEX_WIDTH));
	if (rc->side == 0 && rc->ray_dir_x > 0)
		rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	if (rc->side == 1 && rc->ray_dir_y < 0)
		rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	rc->step = 1.0 * TEX_HEIGHT / rc->line_height;
	rc->tex_pos = (rc->draw_start - SCREEN_HEIGHT / 2 \
		+ rc->line_height / 2) * rc->step;
	rc->y = rc->draw_start - 1;
}

void	draw_texture(t_data *data, t_rc *rc)
{
	while (++rc->y < rc->draw_end)
	{
		rc->tex_y = (int)rc->tex_pos & (TEX_HEIGHT - 1);
		rc->tex_pos += rc->step;
		rc->color = data->texture[rc->tex_num][TEX_HEIGHT \
			* rc->tex_y + rc->tex_x];
		if (rc->side == 1)
			rc->color /= 2;
		my_mlx_pixel_put(data, rc->x, rc->y, rc->color);
	}
}

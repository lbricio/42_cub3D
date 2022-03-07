/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbricio- <lbricio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:44:02 by lbricio-          #+#    #+#             */
/*   Updated: 2022/03/03 17:30:16 by lbricio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	calc_initial_state(t_data *data, t_rc *rc)
{
	rc->render_x = 2 * rc->x / (double)SCREEN_WIDTH - 1;
	rc->map_x = (int)data->pos_x;
	rc->map_y = (int)data->pos_y;
	rc->ray_dir_x = data->dir_x + data->plane_x * rc->render_x;
	rc->ray_dir_y = data->dir_y + data->plane_y * rc->render_x;
	rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
	rc->hit = 0;
}

void	calc_step_and_side_dist(t_data *data, t_rc *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (data->pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - data->pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (data->pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - data->pos_y) * rc->delta_dist_y;
	}
}

void	raycaster(t_data *data)
{
	t_rc	rc;

	rc.x = -1;
	while (++rc.x < SCREEN_WIDTH)
	{
		calc_initial_state(data, &rc);
		calc_step_and_side_dist(data, &rc);
		perform_dda(data, &rc);
		calc_texturing(data, &rc);
		draw_texture(data, &rc);
	}
}

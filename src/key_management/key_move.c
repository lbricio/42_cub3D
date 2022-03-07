/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbricio- <lbricio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:26:38 by lbricio-          #+#    #+#             */
/*   Updated: 2022/03/03 20:26:40 by lbricio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	rotate_left(t_data *data)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(data->rot_speed) \
		- data->dir_y * sin(data->rot_speed);
	data->dir_y = olddir_x * sin(data->rot_speed) \
		+ data->dir_y * cos(data->rot_speed);
	oldplane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(data->rot_speed) \
		- data->plane_y * sin(data->rot_speed);
	data->plane_y = oldplane_x * sin(data->rot_speed) \
		+ data->plane_y * cos(data->rot_speed);
}

void	rotate_right(t_data *data)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(-data->rot_speed) \
		- data->dir_y * sin(-data->rot_speed);
	data->dir_y = olddir_x * sin(-data->rot_speed) \
		+ data->dir_y * cos(-data->rot_speed);
	oldplane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(-data->rot_speed) \
		- data->plane_y * sin(-data->rot_speed);
	data->plane_y = oldplane_x * sin(-data->rot_speed) \
		+ data->plane_y * cos(-data->rot_speed);
}

void	move_forward(t_data *data)
{
	if (data->world_map[(int)(data->pos_x \
		+ data->dir_x * data->move_speed)][(int)data->pos_y] == 0)
		data->pos_x += data->dir_x * data->move_speed;
	if (data->world_map[(int)data->pos_x][(int)(data->pos_y \
		+ data->dir_y * data->move_speed)] == 0)
		data->pos_y += data->dir_y * data->move_speed;
}

void	move_backward(t_data *data)
{
	if (data->world_map[(int)(data->pos_x \
		- data->dir_x * data->move_speed)][(int)data->pos_y] == 0)
		data->pos_x -= data->dir_x * data->move_speed;
	if (data->world_map[(int)data->pos_x][(int)(data->pos_y \
		- data->dir_y * data->move_speed)] == 0)
		data->pos_y -= data->dir_y * data->move_speed;
}

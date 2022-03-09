/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:26:32 by lbricio-          #+#    #+#             */
/*   Updated: 2022/03/09 17:35:21 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	move_left(t_data *data)
{
	if (data->world_map[(int)(data->pos_x \
		- data->plane_x * data->move_speed)][(int)data->pos_y] == 0)
		data->pos_x -= data->plane_x * data->move_speed;
	if (data->world_map[(int)data->pos_x][(int)(data->pos_y \
		- data->plane_y * data->move_speed)] == 0)
		data->pos_y -= data->plane_y * data->move_speed;
}

static void	move_right(t_data *data)
{
	if (data->world_map[(int)(data->pos_x \
		+ data->plane_x * data->move_speed)][(int)data->pos_y] == 0)
		data->pos_x += data->plane_x * data->move_speed;
	if (data->world_map[(int)data->pos_x][(int)(data->pos_y \
		+ data->plane_y * data->move_speed)] == 0)
		data->pos_y += data->plane_y * data->move_speed;
}

int	key_update(t_data *data)
{	
	if (data->key.w)
		move_forward(data);
	if (data->key.s)
		move_backward(data);
	if (data->key.a)
		move_left(data);
	if (data->key.d)
		move_right(data);
	if (data->key.la)
		rotate_left(data);
	if (data->key.ra)
		rotate_right(data);
	if (data->key.esc)
		exit(0);
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	(void)y;
	if (data->key.pause > 0)
	{
		mlx_mouse_move(data->mlx, data->mlx_win, (SCREEN_WIDTH) / 2,
			(SCREEN_HEIGHT) / 2);
		if (x - 10 > (SCREEN_WIDTH) / 2)
			rotate_right(data);
		else if (x + 10 < (SCREEN_WIDTH) / 2)
			rotate_left(data);
	}
	return (0);
}

int	ft_close(t_data *data)
{
	(void) *data;
	mlx_destroy_display(data->mlx);
	mlx_destroy_window(data->mlx, data->mlx_win);
	free(data->mlx);
	free(data->map.no);
	free(data->map.so);
	free(data->map.we);
	free(data->map.ea);
	ft_free_array((char **)data->world_map);
	ft_free_array((char **)data->map.d2);
	exit(0);
}

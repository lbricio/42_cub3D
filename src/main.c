/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbricio- <lbricio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:43:28 by lbricio-          #+#    #+#             */
/*   Updated: 2022/03/08 13:26:31 by lbricio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_input(t_data *data, int argc, char *argv[])
{
	if (simple_arg_check(argc, argv))
		return (FAILURE);
	if (get_map_settings(data, argv[1]))
		return (FAILURE);
	if (build_map_array(data))
		return (FAILURE);
	return (SUCCESS);
}

int	draw_scene(t_data *data)
{
	draw_ceiling(data);
	draw_floor(data);
	raycaster(data);
	draw_minimap(data);
	return (0);
}

int	game_on(t_data *data)
{
	if (data->key.pause > 0)
	{
		data->mlx_img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
		data->mlx_data_addr = mlx_get_data_addr(data->mlx_img, \
			&data->mlx_bits_per_pixel, &data->mlx_size_line, &data->mlx_endian);
		draw_scene(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->mlx_img, 0, 0);
		mlx_destroy_image(data->mlx, data->mlx_img);
		key_update(data);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (get_input(&data, argc, argv) == FAILURE)
		return (FAILURE);
	data.mlx = mlx_init();
	initialize_map(&data);
	data.mlx_win = mlx_new_window(data.mlx, SCREEN_WIDTH, \
		SCREEN_HEIGHT, "Cub3d");
	mlx_mouse_hide();
	mlx_loop_hook(data.mlx, game_on, &data);
	mlx_hook(data.mlx_win, 2, 0, &key_press, &data);
	mlx_hook(data.mlx_win, 3, 0, &key_release, &data);
	mlx_hook(data.mlx_win, 6, 1L << 6, &mouse_move, &data);
	mlx_hook(data.mlx_win, 17, 1L << 2, ft_close, &data);
	mlx_loop(data.mlx);
	return (0);
}

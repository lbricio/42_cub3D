/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_release.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:26:43 by lbricio-          #+#    #+#             */
/*   Updated: 2022/03/08 23:49:19 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	key_press(int key, t_data *data)
{
	if (key == KEY_ESCAPE)
		ft_close(data);
	else if (key == KEY_ANSI_W)
		data->key.w = 1;
	else if (key == KEY_ANSI_S)
		data->key.s = 1;
	else if (key == KEY_ANSI_A)
		data->key.a = 1;
	else if (key == KEY_ANSI_D)
		data->key.d = 1;
	else if (key == KEY_LEFTARROW)
		data->key.la = 1;
	else if (key == KEY_RIGHTARROW)
		data->key.ra = 1;
	else if (key == KEY_PAUSE)
	{
		data->key.pause *= -1;
	}	
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_ESCAPE)
		exit(0);
	else if (key == KEY_ANSI_W)
		data->key.w = 0;
	else if (key == KEY_ANSI_S)
		data->key.s = 0;
	else if (key == KEY_ANSI_A)
		data->key.a = 0;
	else if (key == KEY_ANSI_D)
		data->key.d = 0;
	else if (key == KEY_LEFTARROW)
		data->key.la = 0;
	else if (key == KEY_RIGHTARROW)
		data->key.ra = 0;
	return (0);
}

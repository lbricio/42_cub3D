/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_look.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbricio- <lbricio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:45:57 by lbricio-          #+#    #+#             */
/*   Updated: 2022/03/07 10:47:42 by lbricio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	gnl(char **str, int in)
{
	free((*str));
	(*str) = NULL;
	(*str) = get_next_line(in);
	return (SUCCESS);
}

static int	check_info(t_data *data, char **str, int in)
{
	if ((ft_strncmp((*str), "NO ", 3) && ft_strncmp((*str), "SO ", 3) \
			&& ft_strncmp((*str), "WE ", 3) && ft_strncmp((*str), "EA ", 3) \
			&& ft_strncmp((*str), "F ", 2) && ft_strncmp((*str), "C ", 2)))
	{
		if (!ft_strcmp((*str), "\n"))
			return (gnl(str, in));
		else
		{
			free((*str));
			free(data->map.d1);
			free_path_textures(data);
			return (printf("Error\nInvalid identifier for texture or color\n"));
		}
	}
	else
	{
		if (fill_map_info(data, *str))
		{
			free((*str));
			free(data->map.d1);
			free_path_textures(data);
			return (FAILURE);
		}
	}
	return (gnl(str, in));
}

static int	map_look_2(t_data *data)
{
	if (check_map_for_invalid_char(data, data->map.d1))
	{
		free(data->map.d1);
		free_path_textures(data);
		return (FAILURE);
	}
	if (init_map2d(data))
	{
		free(data->map.d1);
		free_path_textures(data);
		return (FAILURE);
	}
	free(data->map.d1);
	if (is_map_valid(data))
	{
		free_path_textures(data);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	map_look(t_data *data, t_valid *v, char *file, int i)
{
	if (i == 0)
	{
		v->in = open(file, O_RDONLY);
		v->str = get_next_line(v->in);
		if (!v->str)
			return (printf("Error\nEmpty .cub-file\n"));
		v->nl = 0;
		return (init_map_input(data));
	}
	else
	{
		if (map_look_2(data))
			return (FAILURE);
		return (SUCCESS);
	}
}

int	get_map_settings(t_data *data, char *file)
{
	t_valid	v;

	if ((map_look(data, &v, file, 0) > 0) || find_duplicated(&v, v.in, file))
		return (FAILURE);
	while (v.str)
	{
		if (data->map.info != 6)
		{	
			if (check_info(data, &v.str, v.in) > 0)
				return (FAILURE);
			continue ;
		}
		if (!ft_strcmp(v.str, "\n") && v.nl == 0)
		{
			gnl(&v.str, v.in);
			continue ;
		}
		if (!ft_strcmp(v.str, "\n") && v.nl == 1)
			return (printf("Error\nEmpty line in map\n"));
		v.nl = 1;
		data->map.d1 = ft_strjoin(data->map.d1, v.str);
		gnl(&v.str, v.in);
	}
	return (map_look(data, NULL, NULL, 1));
}

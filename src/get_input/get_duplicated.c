/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_duplicated.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbricio- <lbricio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:35:05 by lbricio-          #+#    #+#             */
/*   Updated: 2022/03/08 11:04:27 by lbricio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static char	*get_only_actual(char *str, char *actual)
{
	int	i;

	i = 0;
	while (i <= 199)
		actual[i++] = 0;
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		actual[i] = str[i];
		i++;
	}
	return (actual);
}

static void	pick_info(t_info *info, char *actual)
{
	if (actual == NULL)
	{
		info->no = 0;
		info->so = 0;
		info->ea = 0;
		info->we = 0;
		info->c = 0;
		info->f = 0;
	}
	else
	{
		if (!ft_strncmp(actual, "NO ", 3))
			info->no += 1;
		if (!ft_strncmp(actual, "SO ", 3))
			info->so += 1;
		if (!ft_strncmp(actual, "WE ", 3))
			info->we += 1;
		if (!ft_strncmp(actual, "EA ", 3))
			info->ea += 1;
		if (!ft_strncmp(actual, "F ", 2))
			info->f += 1;
		if (!ft_strncmp(actual, "C ", 2))
			info->c += 1;
	}
}

int	check_picked(t_info *info)
{
	if ((info->no == 1) && (info->so == 1) && (info->we == 1) \
	&& (info->ea == 1) && (info->f == 1) && (info->c == 1))
		return (SUCCESS);
	else
		return (FAILURE);
}

int	find_duplicated(t_valid *v, int in, char *file)
{		
	int		data_count;
	char	*actual;
	t_info	info;

	data_count = 0;
	actual = malloc(800);
	pick_info(&info, NULL);
	while (v->str != NULL)
	{
		actual = get_only_actual(v->str, actual);
		pick_info(&info, actual);
		if (!(ft_strncmp(actual, "NO ", 3)) || !(ft_strncmp(actual, "SO ", 3)) \
		|| !(ft_strncmp(actual, "WE ", 3)) || !(ft_strncmp(actual, "EA ", 3)) \
		|| !(ft_strncmp(actual, "F ", 2)) || !(ft_strncmp(actual, "C ", 2)))
				data_count++;
		gnl(&(v->str), in);
	}
	if (data_count > 6 || check_picked(&info) == 1)
		return (printf("Error\nBad element found\n"));
	close(in);
	free(actual);
	v->in = open(file, O_RDONLY);
	v->str = get_next_line(v->in);
	return (SUCCESS);
}

int	find_omitted(t_valid *v)
{		
	if (!(ft_strncmp(v->str, "NO ", 3)) && !(ft_strncmp(v->str, "SO ", 3)) \
	&& !(ft_strncmp(v->str, "WE ", 3)) && !(ft_strncmp(v->str, "EA ", 3)) \
	&& !(ft_strncmp(v->str, "F ", 2)) && !(ft_strncmp(v->str, "C ", 2)))
		return (SUCCESS);
	else
		return (printf("Error\nOmitted element\n"));
}

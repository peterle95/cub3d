/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:18 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 16:47:26 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_square(t_data *data, int x, int y, int len_side)
{
	int		row;
	int		col;

	row = y;
	while (row < y + len_side)
	{
		col = x;
		while (col < x + len_side)
		{
			if (row >= 0 && row < data->window_height && col
				>= 0 && col < data->window_width)
				put_pixel_to_img(data, col, row, 0x00FFFFFF);
			col++;
		}
		row++;
	}
}

static void	adjust_scaling(t_data *data)
{
	int		greater;

	if (data->map.width > 100 || data->map.height > 100)
		greater = 100;
	else
	{
		if (data->map.height > data->map.width)
			greater = data->map.height;
		else
			greater = data->map.width;
	}
	data->scalar = (data->window_height / greater) / 4;
	data->offset = 0;
}

int	draw_grid(t_data *data)
{
	int		y;
	int		x;

	adjust_scaling(data);
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.map_array[y][x] == '1')
				fill_square(data, (x * data->scalar) + data->offset,
					(y * data->scalar) + data->offset, data->scalar);
			x++;
		}
		y++;
	}
	return (0);
}

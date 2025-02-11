/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:18 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/07 13:36:33 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int	draw_grid(t_data *data)
{
	int	y;
	int	x;
	int	greater;

	data->offset = 0; // for debug visual clarity
	if (data->map.height > data->map.width)
		greater = data->map.height;
	else
		greater = data->map.width;
	data->scalar = (data->window_height / greater) / 4;
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

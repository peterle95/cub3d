/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:18 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/07 12:56:19 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	fill_square(t_data *data, int x, int y, int len_side)
{
	int	row; 
	int	col;

	row = y;
	while (row < y + len_side) 
	{
		col = x;
		while (col < x + len_side)
		{
			if (row >= 0 && row < data->window_height && col >= 0 && col < data->window_width)
				put_pixel_to_img(data, col, row, 0x00FF0000);
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
	data->scalar = (data->window_height / greater) / 2;
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.map_array[y][x] == '1')
				fill_square(data, (x * data->scalar) + data->offset, (y * data->scalar) + data->offset, data->scalar);
			x++;
		}
		y++;
	}
	// t_line	*line;
	// // horizontal
	// y = 0;
	// while (y < data->map.height + 1)
	// {
	// 	// data->map.width -1 seems to work 
	// 	line = init_line(0 + data->offset, (y * data->scalar) + data->offset,
	// 			((data->map.width - 1) * data->scalar) + data->offset, (y * data->scalar) + data->offset);
	// 	compute_line_points(data, line);
	// 	free(line);
	// 	y++;
	// }
	// // vertical
	// x = 0;
	// while (x < data->map.width)
	// {
	// 	line = init_line((x * data->scalar) + data->offset,
	// 			0 + data->offset, (x * data->scalar) + data->offset, (data->map.height * data->scalar) + data->offset);
	// 	compute_line_points(data, line);
	// 	free(line);
	// 	x++;
	// }
	return (0);
}

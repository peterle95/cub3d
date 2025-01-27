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
	int	scalar;
	int	greater;
	int offset = 100; // for debug visual clarity

	if (data->map.height > data->map.width)
		greater = data->map.height;
	else
		greater = data->map.width;
	scalar = data->window_height / greater;
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.map_array[y][x] == '1')
				fill_square(data, (x * scalar) + offset, (y * scalar) + offset, scalar);
			x++;
		}
		y++;
	}
	t_line	*line;
	// horizontal
	y = 0;
	while (y < data->map.height + 1)
	{
		// data->map.width -1 seems to work 
		line = init_line(0 + offset, (y * scalar) + offset,
				((data->map.width - 1) * scalar) + offset, (y * scalar) + offset);
		compute_line_points(data, line);
		free(line);
		y++;
	}
	// vertical
	x = 0;
	while (x < data->map.width)
	{
		line = init_line((x * scalar) + offset,
				0 + offset, (x * scalar) + offset, (data->map.height * scalar) + offset);
		compute_line_points(data, line);
		free(line);
		x++;
	}
	return (0);
}

#include "window.h"

void	fill_square(t_data *data, int x, int y, int len_side)
{
	int	row; 
	int	col;

	row = y;
	while (row < y + len_side) 
	{
		col = x;
		while (col < x + len_side) {
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
	// rather than 1920 needs to be correspoding w or h
	scalar = data->window_height / greater;
	// + 1 to w and h to account for the last cell having a w and h
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
		// why the - 1 to width to make it work? 
		line = init_line(0 + offset, (y * scalar) + offset, ((data->map.width - 1) * scalar) + offset, (y * scalar) + offset);
		compute_line_points(data, line);
		free(line);
		y++;
	}
	// vertical
	x = 0;
	while (x < data->map.width)
	{
		line = init_line((x * scalar) + offset, 0 + offset, (x * scalar) + offset, (data->map.height * scalar) + offset);
		compute_line_points(data, line);
		free(line);
		x++;
	}

	return (0);
}

int	draw(t_data *data)
{
	clear_image_to_colour(data, set_trgb(data->t, data->r, data->g, data->b));
	// obvs don't want to calculate the lines each time through the draw loop
	// t_line	*line;
	// line = init_line(0, 0, 500, 500);
	// compute_line_points(data, line);
	draw_grid(data);
	// free(line);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_data0->img, 0, 0);
	if (data->r > 0)
		data->r--;
	return (0);
}

int	init_data(t_data *data)
{
	data->map.map_array = NULL;
	data->window_width = 1920;
	data->window_height = 1080;
	return (0);
}

// free properly from beginning to avoid mess later
int	main()
{
	printf(">>> Doomed <<<\n");
	t_data	data;

	init_data(&data);
	if(DEBUG)
		printf("DEBUG MODE ON\n");
	if (load_map_data(&data, "test_map2.cub") != 0)
		return (error("Invalid map configuration"));
	if (!validate_map(&data))
		return (error("Invalid map configuration"));
	init_colour_fade(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.window_width, data.window_height, "dooomed");
	mlx_hook(data.mlx_win, 3, 1L << 1, &key_up, &data);
	init_img(&data);
	mlx_loop_hook(data.mlx, &draw, &data);

	// test 
	// mlx_pixel_put(data.mlx, data.mlx_win, 100, 100, 0xFFFFFF);

	mlx_loop(data.mlx);

}


#include "cube3d.h"

int	draw(t_data *data)
{
	int	win_x;
	int	win_y;

	clear_image_to_colour(data, set_trgb(data->t, data->r, data->g, data->b));
	// obvs don't want to calculate the lines each time through the draw loop
	// t_line	*line;
	// line = init_line(0, 0, 500, 500);
	// compute_line_points(data, line);
	draw_grid(data);
	if (mlx_mouse_get_pos(data->mlx, data->mlx_win, &win_x, &win_y))
		printf("Mouse position: (%d, %d)\n", win_x, win_y);
	// free(line);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_data0->img, 0, 0);
	if (data->r > 0)
		data->r--;
	return (0);
}

int	mouse_mv(int mousecode, int x, int y, t_data *data)
{
	(void)data;	
    printf("x: %d y: %d\n", x, y);
    if (mousecode == 1)
		printf("click\n");
	return (0);
}

int mouse_move(int x, int y, t_data *data)
{
	(void)data,
    printf("x: %d y: %d\n", x, y);
	return (0);
}

int	init_data(t_data *data)
{
	data->map.map_array = NULL;
	data->window_width = 1920;
	data->window_height = 1080;
	return (0);
}

int	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, 3, 1L << 1, &key_up, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_down, data);
	mlx_hook(data->mlx_win, 6, 0l, &mouse_move, data);
	mlx_mouse_hook(data->mlx_win, &mouse_mv, data);
	mlx_loop_hook(data->mlx, &draw, data);
	return (0);
}

// free properly from beginning to avoid mess later
int	main()
{
	t_data	data;

	init_data(&data);
	if(DEBUG)
		printf("DEBUG MODE ON\n");
	if (load_map_data(&data, "test_map.cub") != 0)
		return (error("Invalid map configuration"));
	if (!validate_map(&data))
		return (error("Invalid map configuration"));
	init_colour_fade(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.window_width, data.window_height, "dooomed");
	init_img(&data);
	init_hooks(&data);
	mlx_loop(data.mlx);

}


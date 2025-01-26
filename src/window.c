#include "window.h"

// free properly from beginning to avoid mess later

int	draw(t_data *data)
{
	clear_image_to_colour(data, set_trgb(data->t, data->r, data->g, data->b));
	add_random_pixels(data, 1920, 1080, 1000);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_data0->img, 0, 0);
	if (data->r > 0)
		data->r--;
	return (0);
}

int	init_data(t_data *data)
{
	data->map.map_array = NULL;
	return (0);
}

int	main()
{
	printf(">>> Doomed <<<\n");
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
	data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "dooomed");
	mlx_hook(data.mlx_win, 3, 1L << 1, &key_up, &data);
	mlx_hook(data.mlx_win, 17, 0, &terminator, &data);
	init_img(&data);
	mlx_loop_hook(data.mlx, &draw, &data);

	// test 
	// mlx_pixel_put(data.mlx, data.mlx_win, 100, 100, 0xFFFFFF);

	mlx_loop(data.mlx);

}


#include "window.h"

// free properly from beginning to avoid mess later

int draw(t_data *data)
{
    // Clear screen
    clear_image_to_colour(data, set_trgb(data->t, data->r, data->g, data->b)); 
    
    // Calculate ray position and direction
    double camera_x = 0;  // Center of the screen
    double ray_dir_x = data->dir_x + data->plane_x * camera_x;
    double ray_dir_y = data->dir_y + data->plane_y * camera_x;
    
    // Scale player position to screen coordinates
    int screen_pos_x = (int)(data->pos_x * 32); 
    int screen_pos_y = (int)(data->pos_y * 32); 
    
    // Draw a line in the ray direction (for testing)
    int line_length = 300;  // Increased line length to make it more visible
    
    // Draw the ray as a white line
    for (int i = 0; i < line_length; i++)
    {
        int x = screen_pos_x + (int)(ray_dir_x * i);
        int y = screen_pos_y + (int)(ray_dir_y * i);
        if (x >= 0 && x < 960 && y >= 0 && y < 540)
            put_pixel_to_img(data, x, y, set_trgb(0, 255, 255, 255));
    }
    
    // Put the image to window
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_data0->img, 0, 0);
    
    return (0);
}


int	main()
{
	printf(">>> Doomed <<<\n");
	t_data	data;

	data.debug_mode = 0;
	if(data.debug_mode == 0)
		printf("DEBUG MODE ON\n");
	load_map_data(&data, "note");
	if (!validate_map(&data))
		return (error("Invalid map configuration"));
	init_colour_fade(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 960, 540, "dooomed");
	mlx_hook(data.mlx_win, 3, 1L << 1, &key_up, &data);
	init_img(&data);
	if(data.debug_mode == 0)
	{
		// Player position in 2D space
		data.pos_x = 22;  // X coordinate
		data.pos_y = 12;  // Y coordinate

		// Direction vector - where the player is looking
		data.dir_x = -2;  // Looking west (negative x direction)
		data.dir_y = 0;   // No Y component when looking straight north/south

		// Camera plane - defines FOV (Field of View)
		data.plane_x = 0;      // Camera plane perpendicular to direction
		data.plane_y = 0.66;   // This value determines FOV (roughly 66 degrees)

		data.t = 0;
		data.r = 0;
		data.g = 0;
		data.b = 0;
	}
	mlx_loop_hook(data.mlx, &draw, &data);

	// test 
	// mlx_pixel_put(data.mlx, data.mlx_win, 100, 100, 0xFFFFFF);

	mlx_loop(data.mlx);

}


#include "cube3d.h"

// Function to handle window close event
int close_window(t_data *data)
{
    if (data->textures.img[0].ptr)
        mlx_destroy_image(data->mlx, data->textures.img[0].ptr);
    if (data->img_data0->img)
        mlx_destroy_image(data->mlx, data->img_data0->img);
    if (data->mlx_win)
        mlx_destroy_window(data->mlx, data->mlx_win);
    exit(0);
    return (0);
}


int	render_with_transpareny(t_data *data, t_texture *t, int img_x, int img_y)
{
	int	y;
	int	x;
	int pixel;
	int color;

	y = 0;
	while (y < t->height)
	{
		x = 0;
		while (x < t->width)
		{
			pixel = (y * t->size_line) + (x * (t->bpp / 8));
			color = *(int *)(t->addr + pixel);
			if (color != 0xFFFFFF)
				mlx_pixel_put(data->mlx, data->mlx_win, img_x + x, img_y + y, color);
			x++;
		}
		y++;
	}
	return (0);
}

int	draw(t_data *data)
{
	clear_image_to_colour(data, set_trgb(data->t, data->r, data->g, data->b));
	
	// Render the 3D view
	render_frame(data);
	
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_data0->img, 0, 0);
	
	// Draw player sprite if needed
	render_with_transpareny(data, &data->textures.img[0], data->player.x, data->player.y);
	
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

int	init_data(t_data *data)
{
	data->map.map_array = NULL;
	data->window_width = 1920;
	data->window_height = 1080;
	
	// Initialize player position and direction, to be updated with map data
	data->player.x = 22;  // Starting position
	data->player.y = 12;
	data->player.dir_x = -1;  // Initial direction vector
	data->player.dir_y = 0;
	data->player.plane_x = 0;  // Camera plane
	data->player.plane_y = 0.66; // FOV is about 66 degrees
	
	return (0);
}

int	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, 3, 1L << 1, &key_up, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_down, data);
	mlx_hook(data->mlx_win, ClientMessage, 0, close_window, data);
	mlx_mouse_hook(data->mlx_win, &mouse_mv, data);
	mlx_loop_hook(data->mlx, &draw, data);
	return (0);
}

int	load_textures(t_data *data, char *path, char *id)
{
	// load xpm as image
	data->textures.img[0].ptr = mlx_xpm_file_to_image(data->mlx, path,
			&data->textures.img[0].width, &data->textures.img[0].height);
	data->textures.img[0].id = id;
	// load image data to texture object
	data->textures.img[0].addr = mlx_get_data_addr(data->textures.img[0].ptr,
			&(data->textures.img[0].bpp), 
			&(data->textures.img[0].size_line),
			&(data->textures.img[0].endian));
	printf("texture addr: %p\n", data->textures.img[0].addr);
	return (0);	
}

int	init_player(t_data *data)
{
	data->player.x = 0;
	data->player.y = 0;
	data->player.speed = 2;
	return (0);
}

int	player_move(t_data *data, int dir)
{
	if (UP == dir)
		data->player.y -= data->player.speed;
	if (DOWN == dir)
		data->player.y += data->player.speed;
	if (LEFT == dir)
		data->player.x -= data->player.speed;
	if (RIGHT == dir)
		data->player.x += data->player.speed;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (0);
	// valid_path(argv[1])

	init_data(&data);
	if(DEBUG)
		printf("DEBUG MODE ON\n");
	if (load_map_data(&data, argv[1]) != 0)
		return (error("Invalid map configuration"));
	if (!validate_map(&data))
		return (error("Invalid map configuration"));
	init_colour_fade(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.window_width, data.window_height, "dooomed");
	init_img(&data);
	// TODO: load correct textures
	load_textures(&data, "./src/assets/textures/player_marker.xpm", "player_marker");
	init_hooks(&data);
	mlx_mouse_hide(data.mlx, data.mlx_win);
	init_player(&data);
	init_player_position(&data);
	mlx_loop(data.mlx);
}


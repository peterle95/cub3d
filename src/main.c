/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:48 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/07 12:56:49 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// this is probably doubling up terminator function
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


int	render_with_transparency(t_data *data, t_texture *t, int img_x, int img_y)
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

void draw_ceiling(t_data *data)
{
	int		y;
	int		x;
	int		pixel;
	int		color;
	int		sky_x;
	int		texture_offset;
	double	angle;

	// mathsy bit i didn't bother to work out mysedf
	// get player rotation angle from direction vector
	angle = atan2(data->player.dir_y, data->player.dir_x);
    // more maths to map angle (0 to 2π) to sky texture width
    texture_offset = (int)((angle / (2 * M_PI)) * data->textures.img[2].width) % data->textures.img[2].width;
	// wrap around in negative direction
	if (texture_offset < 0)
		texture_offset += data->textures.img[2].width;

	y = 0;
	while (y < data->window_height / 2)
	{
		x = 0;
		while (x < data->window_width)
		{
            sky_x = (x + texture_offset) % data->textures.img[2].width;
			pixel = (y * data->textures.img[2].size_line) + (sky_x * (data->textures.img[2].bpp / 8));
			color = *(int *)(data->textures.img[2].addr + pixel);
            if (color != 0xFFFFFF)
				put_pixel_to_img(data, x, y, color);
			x++;
		}
		y++;
	}
}

int	draw_player_position(t_data *data)
{
	int	centre_x;
	int	centre_y;

	centre_x = data->textures.img[0].width / 2;
	centre_y = data->textures.img[0].height / 2;
	// draw player position
	render_with_transparency(data, &data->textures.img[0],
			(data->player.x * data->scalar)+ data->offset - centre_x,
			(data->player.y * data->scalar) + data->offset - centre_y);
	return (0);
}


// TODO: buffered images
int	draw(t_data *data)
{
	clear_image_to_colour(data, set_trgb(data->t, data->r, data->g, data->b));

	draw_ceiling(data);

	// Render the 3D view
	render_frame(data);

	// currently drawn directly onto window. should be drawn to image
	// draw mini map
	draw_grid(data);
	draw_player_position(data);

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
	mlx_hook(data->mlx_win, 3, 1L << 1, key_up, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_down, data);
	mlx_hook(data->mlx_win, ClientMessage, 0, close_window, data);
	mlx_mouse_hook(data->mlx_win, mouse_mv, data);
	mlx_hook(data->mlx_win, 6, 1L << 6, mouse_move, data);
	mlx_loop_hook(data->mlx, draw, data);
	return (0);
}

int	load_texture(t_data *data, char *path, char *id, int index)
{
	// load xpm as image
	data->textures.img[index].ptr = mlx_xpm_file_to_image(data->mlx, path,
			&data->textures.img[index].width, &data->textures.img[index].height);
	data->textures.img[index].id = id;
	// load image data to texture object
	data->textures.img[index].addr = mlx_get_data_addr(data->textures.img[index].ptr,
			&(data->textures.img[index].bpp), 
			&(data->textures.img[index].size_line),
			&(data->textures.img[index].endian));
	printf("texture addr: %p\n", data->textures.img[index].addr);
	return (0);	
}

// seems as though the player speed must divide into some value
// for the walls to render correctly
int	init_player(t_data *data)
{
	data->player.x = 0;
	data->player.y = 0;
	data->player.speed = 0.5;
	data->player.rotation_speed = 0.1;
	data->player.angle = 0.0;

	return (0);
}

// int	player_move(t_data *data, int dir)
// {
//     double new_x = data->player.x;
//     double new_y = data->player.y;
//
//     if (dir == UP)
//         new_y -= data->player.speed;
//     else if (dir == DOWN)
//         new_y += data->player.speed;
//     else if (dir == LEFT)
//         new_x -= data->player.speed;
//     else if (dir == RIGHT)
//         new_x += data->player.speed;
//
//     // Check if new position is within map bounds
//     if (new_x < 0 || new_x >= data->map.width || new_y < 0 || new_y >= data->map.height)
//         return (0);
//
//     // Check if new position is not a wall
//     if (data->map.map_array[(int)new_y][(int)new_x] != '1') 
// 	{
//         data->player.x = new_x;
//         data->player.y = new_y;
//     }
//     return (0);
// }

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
	load_texture(&data, "./src/assets/textures/player_marker.xpm", "player_marker", 0);
	load_texture(&data, "./src/assets/textures/ceiling.xpm", "wall", 1);
	load_texture(&data, "./src/assets/textures/skybox_4096.xpm", "sky", 2);

	init_hooks(&data);
	mlx_mouse_hide(data.mlx, data.mlx_win);
	init_player(&data);
	init_player_position(&data);
	mlx_loop(data.mlx);
}


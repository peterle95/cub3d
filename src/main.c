/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:48 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/08 12:56:01 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// this is probably doubling up terminator function
// Function to handle window close event
int	close_window(t_data *data)
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

int	mouse_mv(int mousecode, int x, int y, t_data *data)
{
	(void)data;
	printf("x: %d y: %d\n", x, y);
	if (mousecode == 1)
		printf("click\n");
	return (0);
}

int	load_texture(t_data *data, char *path, char *id, int index)
{
	// load xpm as image
	data->textures.img[index].ptr = mlx_xpm_file_to_image(data->mlx, path,
			&data->textures.img[index].width,
			&data->textures.img[index].height);
	data->textures.img[index].id = id;
	// load image data to texture object
	data->textures.img[index].addr = mlx_get_data_addr
		(data->textures.img[index].ptr,
			&(data->textures.img[index].bpp),
			&(data->textures.img[index].size_line),
			&(data->textures.img[index].endian));
	printf("texture addr: %p\n", data->textures.img[index].addr);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (0);
	init_data(&data);
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

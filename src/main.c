/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:48 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/12 14:50:46 by pmolzer          ###   ########.fr       */
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

int	load_texture(t_data *data, char *path, char *id, int index)
{
	if (!path)
	{
		printf("Error: Invalid texture path for %s\n", id);
		return (0);
	}
	data->textures.img[index].ptr = mlx_xpm_file_to_image(data->mlx, path,
			&data->textures.img[index].width,
			&data->textures.img[index].height);		
	if (!data->textures.img[index].ptr)
	{
		printf("Error: Failed to load texture %s at path %s\n", id, path);
		return (0);
	}
	data->textures.img[index].id = id;
	data->textures.img[index].addr = mlx_get_data_addr(data->textures.img[index].ptr,
			&(data->textures.img[index].bpp),
			&(data->textures.img[index].size_line),
			&(data->textures.img[index].endian));		
	if (!data->textures.img[index].addr)
	{
		printf("Error: Failed to get texture data address for %s\n", id);
		mlx_destroy_image(data->mlx, data->textures.img[index].ptr);
		return (0);
	}
	return (1);
}

// some extra checks required to make sure there are textures loaded into config
// and if not that map.config[i] is NULL 
int	load_wall_textures(t_data *data, int i)
{
	if (ft_strncmp(data->map.config[i][0], "WE", 3) == 0)
	{
		if (!load_texture(data, data->map.config[i][1], "wall_texture_west", WEST))
			return (1);
	}
	else if (ft_strncmp(data->map.config[i][0], "EA", 3) == 0)
	{
		if (!load_texture(data, data->map.config[i][1], "wall_texture_east", EAST))
			return (1);
	}
	else if (ft_strncmp(data->map.config[i][0], "NO", 3) == 0)
	{
		if (!load_texture(data, data->map.config[i][1], "wall_texture_north", NORTH))
			return (1);
	}
	else if (ft_strncmp(data->map.config[i][0], "SO", 3) == 0)
	{
		if (!load_texture(data, data->map.config[i][1], "wall_texture_south", SOUTH))
			return (1);
	}
	return (0);
}

// the texture size of the sky should be 360 / player viewing angle * screen width
// since we are only dealing with a fixed window size this can be accounted for easily.
// otherwise some rescaling would have to occur
int correct_texture_resolution(t_data *data, t_texture tex)
{
	(void)data;
	(void)tex;
	return (0);
}

int	load_ceiling_texture(t_data *data, int i)
{
	if (ft_strncmp(data->map.config[i][0], "CE", 3) == 0)
	{
		if (load_texture(data, data->map.config[i][1], "ceiling", CEILING) == 1
				&& correct_texture_resolution(data, data->textures.img[CEILING]) == 0)
			data->ceiling_loaded = 1;
	}
	return (0);
}

// sky texture must be large enough (have default to colour if not big enough)
int	load_textures_from_config(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.config[i])
	{
		if (!data->map.config[i] || array_len(data->map.config[i]) != 2)
			return (1);
		if (load_wall_textures(data, i) != 0)
			return (1);
		load_ceiling_texture(data, i);
		i++;
	}
	return (0);
}

void init_textures(t_data *data)
{
    for (int i = 0; i < MAX_TEXTURES; i++) {
        data->textures.img[i].ptr = NULL;
        data->textures.img[i].addr = NULL;
        data->textures.img[i].width = 0;
        data->textures.img[i].height = 0;
        data->textures.img[i].bpp = 0;
        data->textures.img[i].size_line = 0;
        data->textures.img[i].endian = 0;
        data->textures.img[i].id = NULL;
    }
}

int	main(int argc, char **argv)
{
	t_data data = {0};  // All fields are initialized to 0.

	if (argc != 2)
		return (0);
	init_data(&data);
	if (load_map_data(&data, argv[1]) != 0)
		return (error("Load map data: Invalid map configuration"));
	if (validate_map(&data))
		return (error("(Check map: Invalid map configuration"));
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.window_width, data.window_height, "dooomed");
	init_img(&data);
	init_textures(&data);
	if (load_textures_from_config(&data)) 
		return (error("Failed to load textures"));
	init_hooks(&data);
	mlx_mouse_hide(data.mlx, data.mlx_win);
	init_player(&data);
	init_player_position(&data);
	mlx_loop(data.mlx);
}

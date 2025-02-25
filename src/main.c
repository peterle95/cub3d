/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:48 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/18 13:23:45 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	init_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < MAX_TEXTURES)
	{
		data->textures.img[i].ptr = NULL;
		data->textures.img[i].addr = NULL;
		data->textures.img[i].width = 0;
		data->textures.img[i].height = 0;
		data->textures.img[i].bpp = 0;
		data->textures.img[i].size_line = 0;
		data->textures.img[i].endian = 0;
		data->textures.img[i].id = NULL;
		i++;
	}
}

static void	run_game(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, data->window_width,
			data->window_height, "dooomed");
	init_img(data);
	init_textures(data);
	if (load_textures_from_config(data))
		free_and_terminate(*data, "Failed to load textures");
	init_hooks(data);
	XFixesHideCursor(((t_xvar *)data->mlx)->display,
		((t_win_list *)data->mlx_win)->window);
	init_player(data);
	init_player_position(data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	if (argc != 2 || !has_cub_extension(argv[1]))
		return (error("Usage: ./cub3d <file>.cub", EINVAL));
	if (load_map_data(&data, argv[1]) != 0)
		free_and_terminate(data, "Load map data: Invalid map configuration");
	if (validate_map(&data))
		free_and_terminate(data, "Check map: Invalid map configuration");
	run_game(&data);
	return (0);
}

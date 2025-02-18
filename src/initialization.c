/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:11:37 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/18 13:23:38 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture_struct(t_data *data)
{
	int	i;

	i = 0;
	while (i < N_TEXTURES)
	{
		data->textures.img[i].ptr = NULL;
		data->textures.img[i].id = NULL;
		data->textures.img[i].width = 0;
		data->textures.img[i].height = 0;
		data->textures.img[i].addr = NULL;
		data->textures.img[i].bpp = 0;
		data->textures.img[i].size_line = 0;
		data->textures.img[i].endian = 0;
		i++;
	}
}

int	init_data(t_data *data)
{
	data->map.map_array = NULL;
	data->window_width = 1920;
	data->window_height = 1080;
	data->ceiling_loaded = 0;
	data->map.map_ids = NULL;
	data->map.flat_map = NULL;
	data->map.config = NULL;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->player.x = 0;
	data->player.y = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	data->scalar = 1;
	data->fnbl = 0;
	init_texture_struct(data);
	return (0);
}

int	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, 3, 1L << 1, key_up, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_down, data);
	mlx_hook(data->mlx_win, ClientMessage, 0, close_window, data);
	mlx_hook(data->mlx_win, 6, 1L << 6, mouse_move, data);
	mlx_loop_hook(data->mlx, draw, data);
	return (0);
}

int	init_player(t_data *data)
{
	data->player.x = 0;
	data->player.y = 0;
	data->player.speed = 0.5;
	data->player.rotation_speed = 0.1;
	data->player.angle = 0.0;
	return (0);
}

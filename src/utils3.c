/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:01:49 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:07:58 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
		return (return_bad_texture(id, path));
	data->textures.img[index].id = id;
	data->textures.img[index].addr
		= mlx_get_data_addr(data->textures.img[index].ptr,
			&(data->textures.img[index].bpp),
			&(data->textures.img[index].size_line),
			&(data->textures.img[index].endian));
	if (!data->textures.img[index].addr)
		return (return_bad_image(data, index, id));
	return (1);
}

int	load_wall_textures(t_data *data, int i)
{
	if (ft_strncmp(data->map.config[i][0], "WE", 3) == 0)
	{
		if (!load_texture(data, data->map.config[i][1],
			"wall_texture_west", WEST))
			return (1);
	}
	else if (ft_strncmp(data->map.config[i][0], "EA", 3) == 0)
	{
		if (!load_texture(data, data->map.config[i][1],
			"wall_texture_east", EAST))
			return (1);
	}
	else if (ft_strncmp(data->map.config[i][0], "NO", 3) == 0)
	{
		if (!load_texture(data, data->map.config[i][1],
			"wall_texture_north", NORTH))
			return (1);
	}
	else if (ft_strncmp(data->map.config[i][0], "SO", 3) == 0)
	{
		if (!load_texture(data, data->map.config[i][1],
			"wall_texture_south", SOUTH))
			return (1);
	}
	return (0);
}

int	correct_texture_resolution(t_data *data, t_texture tex)
{
	if (tex.width < data->window_width
		|| tex.height < data->window_height / 2)
		return (1);
	return (0);
}

int	load_ceiling_texture(t_data *data, int i)
{
	if (ft_strncmp(data->map.config[i][0], "CE", 3) == 0)
	{
		if (load_texture(data, data->map.config[i][1], "ceiling", CEILING) == 1
				&& correct_texture_resolution(data,
					data->textures.img[CEILING]) == 0)
			data->ceiling_loaded = 1;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:06:27 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/18 13:39:10 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_config_colors(t_data *data,
		char **floor_color, char **ceiling_color)
{
	int		i;

	i = 0;
	while (data->map.config[i])
	{
		if (ft_strncmp(data->map.config[i][0], "F", 2) == 0)
			*floor_color = data->map.config[i][1];
		else if (ft_strncmp(data->map.config[i][0], "C", 2) == 0)
			*ceiling_color = data->map.config[i][1];
		i++;
	}
	return (0);
}

static int	validate_colors(char *floor_color, char *ceiling_color,
			unsigned int floor_rgb[3], unsigned int ceiling_rgb[3])
{
	if (!floor_color || !ceiling_color
		|| validate_rgb(floor_color, floor_rgb) != 0
		|| validate_rgb(ceiling_color, ceiling_rgb) != 0)
	{
		error("Color did not load", EINVAL);
		return (1);
	}
	return (0);
}

static void	set_colors(t_data *data, unsigned int floor_rgb[3],
		unsigned int ceiling_rgb[3])
{
	data->map.floor_color = (floor_rgb[0] << 16)
		| (floor_rgb[1] << 8) | floor_rgb[2];
	data->map.ceiling_color = (ceiling_rgb[0] << 16)
		| (ceiling_rgb[1] << 8) | ceiling_rgb[2];
}

int	validate_map(t_data *data)
{
	char			*floor_color;
	char			*ceiling_color;
	unsigned int	floor_rgb[3];
	unsigned int	ceiling_rgb[3];

	floor_color = NULL;
	ceiling_color = NULL;
	if (validate_textures(data) != 0)
		return (1);
	if (validate_map_chars(data->map.map_array, "01NSEW ") != 0)
		return (1);
	process_config_colors(data, &floor_color, &ceiling_color);
	if (validate_colors(floor_color, ceiling_color, floor_rgb, ceiling_rgb))
		return (1);
	set_colors(data, floor_rgb, ceiling_rgb);
	if (is_surrounded_by_walls(data->map.map_array,
			data->map.height, data->map.width))
		return (1);
	if (validate_player_inside_map(data->map.map_array,
			data->map.height, data->map.width))
		return (1);
	return (0);
}

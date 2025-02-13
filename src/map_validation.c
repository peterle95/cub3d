/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:06:27 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 18:33:10 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// Helper function to free a NULL-terminated array of strings.
static void	free_split(char **tokens)
{
	int		k;

	k = 0;
	while (tokens[k])
	{
		free(tokens[k]);
		k++;
	}
	free(tokens);
}

static int	validate_number_string(const char *str)
{
	int		j;

	if (str[0] == '\0')
		return (1);
	j = 0;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			return (1);
		j++;
	}
	return (0);
}

static int	validate_rgb_value(const char *value)
{
	unsigned int	num;

	if (validate_number_string(value))
		return (1);
	num = ft_atoi(value);
	if (num > 255)
		return (1);
	return (0);
}

static int	process_rgb_values(char **values, unsigned int rgb[3])
{
	int		i;

	i = 0;
	while (i < 3 && values[i])
	{
		if (validate_rgb_value(values[i]))
			return (1);
		rgb[i] = ft_atoi(values[i]);
		i++;
	}
	if (i != 3 || values[i] != NULL)
		return (1);
	return (0);
}

static int	validate_rgb(const char *color, unsigned int rgb[3])
{
	char	**values;
	int		result;

	values = ft_split(color, ',');
	if (!values)
		return (1);
	result = process_rgb_values(values, rgb);
	free_split(values);
	return (result);
}

static int	check_top(char **map, int i, int j)
{
	size_t	line_len;

	if (i == 0)
	{
		printf("Error: Map not closed at position [%d][%d] (top)\n", i, j);
		return (1);
	}
	line_len = ft_strlen(map[i-1]);
	if (!map[i-1][j] || ((size_t)j >= line_len) || map[i-1][j] == ' ')
	{
		printf("Error: Map not closed at position [%d][%d] (top)\n", i, j);
		return (1);
	}
	return (0);
}

static int	check_bottom(char **map, int i, int j, int height)
{
	size_t	line_len;

	if (i == height-1)
	{
		printf("Error: Map not closed at position [%d][%d] (bottom)\n", i, j);
		return (1);
	}
	line_len = ft_strlen(map[i+1]);
	if (!map[i+1][j] || ((size_t)j >= line_len) || map[i+1][j] == ' ')
	{
		printf("Error: Map not closed at position [%d][%d] (bottom)\n", i, j);
		return (1);
	}
	return (0);
}

static int	check_left(char **map, int i, int j)
{
	if (j == 0 || map[i][j-1] == ' ')
	{
		printf("Error: Map not closed at position [%d][%d] (left)\n", i, j);
		return (1);
	}
	return (0);
}

static int	check_right(char **map, int i, int j)
{
	if (!map[i][j+1] || map[i][j+1] == ' ')
	{
		printf("Error: Map not closed at position [%d][%d] (right)\n", i, j);
		return (1);
	}
	return (0);
}

static int	is_surrounded_by_walls(char **map, int height, int width)
{
	int		i;
	int		j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width && map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (check_top(map, i, j) || check_bottom(map, i, j, height)
					|| check_left(map, i, j) || check_right(map, i, j))
					return (1);
			}
		}
	}
	return (0);
}

static int	process_row(char *row, char *valid_chars, int *player_count)
{
	int		j;

	j = -1;
	while (row[++j])
	{
		if (!ft_strchr(valid_chars, row[j]))
		{
			error("Error: Invalid character in map");
			return (1);
		}
		if (ft_strchr(VALID_PLAYER_CHARS, row[j]))
			(*player_count)++;
	}
	return (0);
}

static int	check_player_count(int count)
{
	if (count != 1)
	{
		error("Error: There must be exactly one player in the map");
		return (1);
	}
	return (0);
}

static int	validate_map_chars(char **map, char *valid_chars)
{
	int		i;
	int		player_count;

	player_count = 0;
	i = -1;
	while (map[++i])
	{
		if (process_row(map[i], valid_chars, &player_count))
			return (1);
	}
	return (check_player_count(player_count));
}

static int	try_path_with_prefix(char *path, char *prefix)
{
	char	*full_path;
	int		fd;

	full_path = ft_strjoin(prefix, path);
	if (!full_path)
		return (0);
	fd = open(full_path, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		free(full_path);
		return (1);
	}
	free(full_path);
	return (0);
}

static int	validate_texture_path(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	if (try_path_with_prefix(path, "src/"))
		return (1);
	if (try_path_with_prefix(path, "./"))
		return (1);
	return (0);
}

// N_TEXTURES - 2 because last 2 elements of
// map.config are colors
static int	validate_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < N_TEXTURES - 2)
	{
		if (data->map.conifig[i]
			&& ft_strncmp(data->map.config[i][0], "F", 2) != 0
				&& ft_strncmp(data->map.config[i][0], "C", 2) != 0)
		{
			if (!validate_texture_path(data->map.config[i][1]))
				return (-1);
		}
		i++;
	}
	return (0);
}

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
		printf("color did not load\n");
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
	char	*floor_color;
	char	*ceiling_color;
	unsigned int		floor_rgb[3];
	unsigned int		ceiling_rgb[3];

	floor_color = NULL;
	ceiling_color = NULL;
	if (!data)
	{
		error("Error: Map data not properly initialized");
		return (1);
	}
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
	return (0);
}

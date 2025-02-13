/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:06:27 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 17:58:18 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// Helper function to free a NULL-terminated array of strings.
static void free_split(char **tokens)
{
    int k = 0;
    while (tokens[k])
    {
        free(tokens[k]);
        k++;
    }
    free(tokens);
}

static int validate_rgb(const char *color, unsigned int rgb[3])
{
    char **values;
    int i;
    int j;

    values = ft_split(color, ',');
    if (!values)
        return (1);

    i = 0;
    while (i < 3 && values[i])
    {
        if (values[i][0] == '\0')
        {
            free_split(values);
            return (1);
        }
        j = 0;
        while (values[i][j])
        {
            if (!ft_isdigit(values[i][j]))
            {
                free_split(values);
                return (1);
            }
            j++;
        }
        rgb[i] = ft_atoi(values[i]);
        if (rgb[i] > 255)
        {
            free_split(values);
            return (1);
        }
        i++;
    }
    if (i != 3 || values[i] != NULL)
    {
        free_split(values);
        return (1);
    }
    free_split(values);
    return (0);
}

static int is_surrounded_by_walls(char **map, int height, int width)
{
    size_t line_len;
    int i;
    int j;

    i = 0;
    while (i < height) 
    {
        j = 0;
        while (j < width && map[i][j]) 
        {
            if (map[i][j] == '0') 
            {
                if (i == 0) 
                {
                    printf("Error: Map not closed at position [%d][%d] (top)\n", i, j);
                    return 1;
                }
                line_len = ft_strlen(map[i-1]);
                if (!map[i-1][j] || ((size_t)j >= line_len) || map[i-1][j] == ' ') 
                {
                    printf("Error: Map not closed at position [%d][%d] (top)\n", i, j);
                    return 1;
                }
                if (i == height-1) 
                {
                    printf("Error: Map not closed at position [%d][%d] (bottom)\n", i, j);
                    return 1;
                }
                line_len = ft_strlen(map[i+1]);
                if (!map[i+1][j] || ((size_t)j >= line_len) || map[i+1][j] == ' ') 
                {
                    printf("Error: Map not closed at position [%d][%d] (bottom)\n", i, j);
                    return 1;
                }
                if (j == 0 || map[i][j-1] == ' ') 
                {
                    printf("Error: Map not closed at position [%d][%d] (left)\n", i, j);
                    return 1;
                }
                if (!map[i][j+1] || map[i][j+1] == ' ') 
                {
                    printf("Error: Map not closed at position [%d][%d] (right)\n", i, j);
                    return 1;
                }
            }
            j++;
        }
        i++;
    }
    return 0;
}


static int validate_map_chars(char **map, char *valid_chars)
{
    int i;
    int j;
    int player_count;

    player_count = 0;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (!ft_strchr(valid_chars, map[i][j]))
            {
                error("Error: Invalid character in map");
                return (1);
            }
            if (ft_strchr(VALID_PLAYER_CHARS, map[i][j]))
                player_count++;
            j++;
        }
        i++;
    }
    if (player_count != 1)
	{
        error("Error: There must be exactly one player in the map");
    	return (1);
	}
	return (0);
}

static int validate_texture_path(char *path)
{
    char *full_path;
    int fd;

    fd = open(path, O_RDONLY);
    if (fd != -1)
    {
        close(fd);
        return (1);
    }
    full_path = ft_strjoin("src/", path);
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
    full_path = ft_strjoin("./", path);
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

// N_TEXTURES - 2 because last 2 elements of
// map.config are colors
static int	validate_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < N_TEXTURES - 2)
	{
		if (data->map.config[i] && ft_strncmp(data->map.config[i][0], "F", 2) != 0
				&& ft_strncmp(data->map.config[i][0], "C", 2) != 0)
		{
			if (!validate_texture_path(data->map.config[i][1]))
				return (-1);
		}
		i++;
	}
	return (0);
}

int validate_map(t_data *data)
{
    char *floor_color;
    char *ceiling_color;
	int i;
    unsigned int floor_rgb[3];
    unsigned int ceiling_rgb[3];
    
    if (!data)
    {
        error("Error: Map data not properly initialized");
        return (1);
    }
	if (validate_textures(data) != 0)
		return (1);
    if (validate_map_chars(data->map.map_array, "01NSEW ") != 0)
		return (1);
    floor_color = NULL;
    ceiling_color = NULL;
	i = 0;
	while (data->map.config[i]) 
	{
        if (ft_strncmp(data->map.config[i][0], "F", 2) == 0)
            floor_color = data->map.config[i][1];
        else if (ft_strncmp(data->map.config[i][0], "C", 2) == 0)
            ceiling_color = data->map.config[i][1];
		i++;
    }
    if (!floor_color || !ceiling_color || 
        validate_rgb(floor_color, floor_rgb) != 0 || 
        validate_rgb(ceiling_color, ceiling_rgb) != 0)
	{
		printf("color did not load\n");
        return (1);
	}
    data->map.floor_color = (floor_rgb[0] << 16) | (floor_rgb[1] << 8) | floor_rgb[2];
    data->map.ceiling_color = (ceiling_rgb[0] << 16) | (ceiling_rgb[1] << 8) | ceiling_rgb[2];
    if (is_surrounded_by_walls(data->map.map_array, data->map.height, data->map.width))
        return (1);
    return (0);
}

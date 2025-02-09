/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:06:27 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/09 11:14:31 by pmolzer          ###   ########.fr       */
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

static int validate_rgb(char *color)
{
    int comma_count = 0;
    int i = 0;
    int rgb[3];

    // Check that the input is not NULL or an empty string
    if (!color || color[0] == '\0')
        return (1);

    // Make sure the string has exactly two commas.
    while (color[i])
    {
        if (color[i] == ',')
            comma_count++;
        i++;
    }
    if (comma_count != 2)
        return (1);

    // Split the string using comma as delimiter.
    char **values = ft_split(color, ',');
    if (!values)
        return (1);

    i = 0;
    while (i < 3 && values[i])
    {
        // Check that the token is not an empty string.
        if (values[i][0] == '\0')
        {
            free_split(values);
            return (1);
        }
        int j = 0;
        // Check that each character in this token is a digit.
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
        if (rgb[i] < 0 || rgb[i] > 255)
        {
            free_split(values);
            return (1);
        }
        i++;
    }
    // If we did not get exactly 3 values, that is an error.
    if (i != 3 || values[i] != NULL)
    {
        free_split(values);
        return (1);
    }
    free_split(values);
    return (0);
}

/* static int is_surrounded_by_walls(char **map, int height, int width)
{
  int i;
  int j;

    i = 0;
    j = 0;

  while(i < height)
  {
    while (j < width)
    {
      if (map[i][j] != '1' && map[i][j] != ' ')
      {
        // Check all adjacent cells
        if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
          return (0);
        if (map[i-1][j] == ' ' || map[i+1][j] == ' ' || 
          map[i][j-1] == ' ' || map[i][j+1] == ' ')
          return (0);
      }
      j++;
    }
    i++;
  }
  return (1);
} */

static int is_surrounded_by_walls(char **map, int height, int width)
{
    size_t line_len;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width && map[i][j]; j++) {
            if (map[i][j] == '0') {
                // Check up
                if (i == 0) {
                    printf("Error: Map not closed at position [%d][%d] (top)\n", i, j);
                    return 1;
                }
                line_len = ft_strlen(map[i-1]);
                if (!map[i-1][j] || ((size_t)j >= line_len) || map[i-1][j] == ' ') {
                    printf("Error: Map not closed at position [%d][%d] (top)\n", i, j);
                    return 1;
                }
                
                // Check down
                if (i == height-1) {
                    printf("Error: Map not closed at position [%d][%d] (bottom)\n", i, j);
                    return 1;
                }
                line_len = ft_strlen(map[i+1]);
                if (!map[i+1][j] || ((size_t)j >= line_len) || map[i+1][j] == ' ') {
                    printf("Error: Map not closed at position [%d][%d] (bottom)\n", i, j);
                    return 1;
                }
                
                // Check left
                if (j == 0 || map[i][j-1] == ' ') {
                    printf("Error: Map not closed at position [%d][%d] (left)\n", i, j);
                    return 1;
                }
                
                // Check right
                if (!map[i][j+1] || map[i][j+1] == ' ') {
                    printf("Error: Map not closed at position [%d][%d] (right)\n", i, j);
                    return 1;
                }
            }
        }
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
        error("Error: There must be exactly one player in the map");
    return (player_count == 1);
}

// This function validates the texture path provided for a texture file.
static int validate_texture_path(char *path)
{
    char *full_path;
    int fd;
    
    // Try direct path first
    fd = open(path, O_RDONLY);
    if (fd != -1)
    {
        close(fd);
        return (1);
    }

    // Try with src/ prefix
    full_path = ft_strjoin("src/", path);
    fd = open(full_path, O_RDONLY);
    if (fd != -1)
    {
        close(fd);
        free(full_path);
        return (1);
    }
    free(full_path);

    // Try with ./ prefix
    full_path = ft_strjoin("./", path);
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

static int	validate_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < N_TEXTURES)
	{
		if (!validate_texture_path(data->map.config[i][1]))
			return (-1);
		i++;
	}
	return (0);
}

int validate_map(t_data *data)
{
    // Check if data or map is NULL
    if (!data || !data->map.config[0][1] || !data->map.config[1][1] || 
        !data->map.config[2][1] || !data->map.config[3][1])
    {
        error("Error: Map data not properly initialized");
        return (1);
    }

    // validate .cub map
	if (validate_textures(data) != 0)
		return (1);
    // Validate map characters and player count
    if (!validate_map_chars(data->map.map_array, "01NSEW"))
        return (1);

    // Validate colors (F and C)
    char *floor_color = NULL;
    char *ceiling_color = NULL;
    
    for (int i = 0; data->map.config[i]; i++) {
        if (ft_strncmp(data->map.config[i][0], "F", 2) == 0)
            floor_color = data->map.config[i][1];
        else if (ft_strncmp(data->map.config[i][0], "C", 2) == 0)
            ceiling_color = data->map.config[i][1];
    }
    
    if (!floor_color || !ceiling_color || 
        validate_rgb(floor_color) != 0 || 
        validate_rgb(ceiling_color) != 0)
        return (1);

    // Validate map is surrounded by walls
    if (!is_surrounded_by_walls(data->map.map_array, data->map.height, data->map.width))
        return (1);

    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:06:27 by pmolzer           #+#    #+#             */
/*   Updated: 2025/01/22 16:43:13 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static int	validate_rgb(char *color)
{
    // refactor this function
	char	**values;
	int		rgb[3];
	int		i;
	int		j;

	values = ft_split(color, ',');
	if (!values)
		return (1);
	i = 0;
	while (values[i] && i < 3)
	{
		j = 0;
		// Check if each character in the string is a digit
		while (values[i][j])
		{
			if (!ft_isdigit(values[i][j]))
			{
				// Free values array before returning
				while (values[i])
					free(values[i++]);
				free(values);
				return (1);
			}
			j++;
		}
		rgb[i] = ft_atoi(values[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
		// Free values array before returning
			while (values[i])
				free(values[i++]);
			free(values);
			return (1);
		}
		i++;
	}
	if (i != 3 || values[i] != NULL)
	{
		// Free values array before returning
		while (values[i])
			free(values[i++]);
		free(values);
		return (1);
	}
  // Free values array before returning success
	i = 0;
	while (values[i])
		free(values[i++]);
	free(values);
	return (0);
}

static int is_surrounded_by_walls(char **map, int height, int width)
{
	size_t	line_len;
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		line_len = ft_strlen(map[i]);
		if (line_len > (size_t)width)  // Check if line exceeds map width
		{
			printf("Error: Line %d exceeds map width\n", i);
			return (1);
		}
		while (map[i][j] && j < width)
		{
			if (map[i][j] == '0') 
			{
				// Check up
				if (i == 0) 
				{
					printf("Error: Map not closed at position [%d][%d] (top)\n", i, j);
					return (1);
				}
				if (j >= width || !map[i-1][j] || map[i-1][j] == ' ') 
				{
					printf("Error: Map not closed at position [%d][%d] (top)\n", i, j);
					return (1);
				}
				
				// Check down
				if (i == height-1) 
				{
					printf("Error: Map not closed at position [%d][%d] (bottom)\n", i, j);
					return (1);
				}
				if (j >= width || !map[i+1][j] || map[i+1][j] == ' ') 
				{
					printf("Error: Map not closed at position [%d][%d] (bottom)\n", i, j);
					return (1);
				}
				
				// Check left
				if (j == 0 || map[i][j-1] == ' ') 
				{
					printf("Error: Map not closed at position [%d][%d] (left)\n", i, j);
					return (1);
				}
				
				// Check right
				if (j == width-1 || !map[i][j+1] || map[i][j+1] == ' ') 
				{
					printf("Error: Map not closed at position [%d][%d] (right)\n", i, j);
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}


static int	validate_map_chars(char **map)
{
	int		i;
	int		j;
	int		player_count;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(VALID_MAP_CHARS, map[i][j]))
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
	return (0);
}

// This function validates the texture path provided for a texture file.
static int	validate_texture_path(char *path)
{
	int		fd;

	if (!path || !ft_strnstr(path, ".xpm", ft_strlen(path)))
		return (1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error("Error: Failed to open texture file");
		return (1);
	}
	close(fd);
	return (0);
}

static void test_map_validation() 
{
    // remove this function before evaluating
    char *valid_map[] = 
    {
        "11111111",
        "10000001",
        "10000001",
        "11111111",
        NULL
        };

        char *invalid_map[] = 
        {
        "11111111",
        "10000001",
        "10000000",  // gap in right wall
        "11111111",
        NULL
        };

        char *irregular_map[] = 
        {
        "  11111",
        "  10001",
        "11100011",
        "10000001",
        "11111111",
        NULL
        };

        char *complex_map[] = 
        {
        "  11111",
        "  10001",
        "11100011",
        "10000001",
        "11111101          1111111111",
        "    1001          1001   101",
        "111110001         1001111101",
        "1000000001        1000000001",
        "1000000001111111111000000001",
        "1000000000000000000000000001",
        "100000000000000000000000001", 
        " 11111111111111111111111111",
        NULL,
        };

        char *complex_map_2[] = 
        {
        "    1111          1111111111                          ",
        "    1001          1001   101                          ",
        "111110001         1001111101                          ",
        "1000000001        1000000001                          ",
        "1000000001111111111000000001    1111111111111111111111",
        "1000000000000000000000000001    1000000000000000000001",
        "100000000000000000000000001     1000000000000000000001", 
        " 10000111111111111111100001     1000000000000000000001",
        " 100001              100001111111000000000000000000001",
        " 100001              100000000000000000000000000000001",
        " 100001              100001111110000000000000000000001",
        " 111111              100001    10000000000000000000001",
        "              1111111100001    10000000000000000000001",
        "111111111111111000000000001    11111111111111111111111",
        "100000000000000000111111111                           ",
        "100000000000001111                                    ",
        "111111111111111              0                        ",
        NULL,
    };

    printf("Testing valid map:\n");
    if (!is_surrounded_by_walls(valid_map, 4, 8))
        printf("Valid map test passed!\n\n");
    else
        printf("Valid map test failed!\n\n");

    printf("Testing invalid map:\n");
    if (is_surrounded_by_walls(invalid_map, 4, 8))
        printf("Invalid map test caught the error (as expected)!\n\n");
    else
        printf("Invalid map test failed to catch the error!\n\n");

    printf("Testing irregular map:\n");
    if (!is_surrounded_by_walls(irregular_map, 5, 8))
        printf("Irregular map test passed!\n\n");
    else
        printf("Irregular map test failed!\n\n");

    printf("Testing complex map:\n");
    if (!is_surrounded_by_walls(complex_map, 12, 28))
        printf("Complex map test passed!\n\n");
    else
        printf("Complex map test failed!\n\n");

    printf("Testing complex map 2:\n");
    if (!is_surrounded_by_walls(complex_map_2, 17, 54))
        printf("Complex map 2 test passed!\n\n");
    else
        printf("Complex map 2 test failed!\n\n");
}

int validate_map(t_data *data)
{
    if(data->debug_mode == 0)
        test_map_validation();
    // Check if data or map is NULL
    if (!data || !data->map.no || !data->map.so || 
        !data->map.we || !data->map.ea)
    {
        error("Error: Map data not properly initialized");
        return (1);
    }

    // validate .cub map
    
    if (!validate_texture_path(data->map.no) || !validate_texture_path(data->map.so) ||
        !validate_texture_path(data->map.we) || !validate_texture_path(data->map.ea))
        return (1);
    // Validate map characters and player count
    if (!validate_map_chars(data->map.map_array))
        return (1);

    // Validate colors
    if (!validate_rgb(data->map.f) || !validate_rgb(data->map.c))
        return (1);

    // Validate map is surrounded by walls
    /* if (!is_surrounded_by_walls(data->map.map_array, data->map.map_height, 
               data->map.map_width))
        return (1); */

    return (0);
}

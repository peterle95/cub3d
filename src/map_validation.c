/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:06:27 by pmolzer           #+#    #+#             */
/*   Updated: 2025/01/20 11:51:47 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

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
                return (0);
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
    int fd;

    if (!path || !ft_strnstr(path, ".xpm", ft_strlen(path)))
        return (0);
    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        error("Error: Failed to open texture file");
        return (0);
    }
    close(fd);
    return (1);
}

int validate_map(t_data *data)
{
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
    if (!validate_map_chars(data->map.map_array, "01"))
        return (1);

    // Validate colors
    // TODO: Implement color validation for floor and ceiling (data->map.f and data->map.c)

    // Validate map is surrounded by walls
    // TODO: Check that the first and last rows of the map are all walls (1)
    // TODO: Check that the first and last columns of each row are all walls (1)
    // TODO: Ensure that there are no gaps in the walls

    return (0);
}




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:06:27 by pmolzer           #+#    #+#             */
/*   Updated: 2025/01/19 14:55:36 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

// This function validates the texture path provided for a texture file.
static int validate_texture_path(char *path)
{
    int fd;

    if (!path || !ft_strnstr(path, ".cub", ft_strlen(path)))
        return (0);
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (0);
    close(fd);
    return (1);
}

int validate_map(t_data *data)
{
    if (!validate_texture_path(data->map.no) || !validate_texture_path(data->map.so) ||
        !validate_texture_path(data->map.we) || !validate_texture_path(data->map.ea))
        return (1);

    // Validate colors
    // TODO: Implement color validation for floor and ceiling (data->map.f and data->map.c)

    // Validate map characters and player count
    // TODO: Check that the map contains only valid characters (0, 1, N, S, E, W)
    // TODO: Ensure there is exactly one player start position (N, S, E, W)

    // Validate map is surrounded by walls
    // TODO: Check that the first and last rows of the map are all walls (1)
    // TODO: Check that the first and last columns of each row are all walls (1)
    // TODO: Ensure that there are no gaps in the walls

    return (0);
}




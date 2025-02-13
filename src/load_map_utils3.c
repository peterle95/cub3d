/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:11:36 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 15:13:12 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void cleanup_on_error(t_data *data, int row)
{
    while (row-- > 0)
        free(data->map.map_array[row]);
    free(data->map.map_array);
    error("Error: Failed to allocate row for map.array.");
}

int	flat_map_to_map_array(t_data *data)
{
    int	i;

    if (allocate_map_array(data))
        return (1);

    i = 0;
    while (i < data->map.height)
    {
        if (allocate_and_init_row(data, i))
        {
            cleanup_on_error(data, i);
            return (1);
        }
        i++;
    }

    if (copy_chars(data, data->map.flat_map))
        return (1);
    return (0);
}

int	load_map_clean_up(t_data *data, char *line, int fd)
{
	(void)data;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(data->map.flat_map);
	return(-1);
}

int check_file_readable(const char *f_name)
{
    int     fd;
    char    buff;
    
    fd = open(f_name, O_RDONLY);
    if (fd < 0)
    {
        error("Error: Unable to open file for reading (first open).");
        return (1);
    }
    if (read(fd, &buff, 1) < 1)
    {
        close(fd);
        error("Error: File is empty or unreadable.");
        return (1);
    }
    close(fd);
    return (0);
}
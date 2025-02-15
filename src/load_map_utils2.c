/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:06:08 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_map_file(const char *f_name)
{
	int		fd;

	fd = open(f_name, O_RDONLY);
	if (fd < 0)
	{
		error("Unable to open file for reading (second open)", errno);
		return (-1);
	}
	return (fd);
}

int	process_single_line(t_data *data, char *line, int fd)
{
	if (line && parse_line(data, line) != 0)
	{
		load_map_clean_up(data, line, fd);
		return (1);
	}
	return (0);
}

int	process_map_lines(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (process_single_line(data, line, fd))
		return (1);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (process_single_line(data, line, fd))
			return (1);
	}
	return (0);
}

void	debug_print_map(t_data *data)
{
	if (DEBUG)
	{
		printf("map_array:\n");
		print_string_array(data->map.map_array, data->map.height);
	}
}

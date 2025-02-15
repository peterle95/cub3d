/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:41 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_map_ids_array(t_data *data)
{
	data->map.map_ids = malloc((N_CONFIGS + 1) * sizeof(char *));
	if (!data->map.map_ids)
	{
		error("Failed to allocate map.map_ids", ENOMEM);
		free(data->map.config);
		return (1);
	}
	return (0);
}

void	set_map_ids(t_data *data)
{
	data->map.map_ids[0] = "NO";
	data->map.map_ids[1] = "SO";
	data->map.map_ids[2] = "WE";
	data->map.map_ids[3] = "EA";
	data->map.map_ids[4] = "CE";
	data->map.map_ids[5] = "F";
	data->map.map_ids[6] = "C";
	data->map.map_ids[N_CONFIGS] = NULL;
}

int	init_ids(t_data *data)
{
	data->map.width = 0;
	data->map.height = 0;
	if (init_flat_map(data))
		return (1);
	if (init_config(data))
		return (1);
	if (init_map_ids_array(data))
		return (1);
	set_map_ids(data);
	data->map.id = 0;
	return (0);
}

int	load_map_data(t_data *data, char *f_name)
{
	int		fd;

	init_ids(data);
	if (check_file_readable(f_name))
		return (1);
	fd = open_map_file(f_name);
	if (fd < 0)
		return (1);
	if (process_map_lines(data, fd))
		return (1);
	if (flat_map_to_map_array(data))
	{
		error("Bad configuration file", EINVAL);
	}
	load_map_clean_up(data, NULL, fd);
	debug_print_map(data);
	return (0);
}

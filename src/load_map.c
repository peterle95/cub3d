/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:41 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 15:22:07 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int init_flat_map(t_data *data)
{
    data->map.flat_map = ft_strdup("");
    if (!data->map.flat_map)
    {
        error("Error: Failed to allocate flat_map.");
        return (1);
    }
    return (0);
}

int init_config(t_data *data)
{
    int i;

    data->map.config = malloc((N_CONFIGS + 1) * sizeof(char **));
    if (!data->map.config)
    {
        error("Error: Failed to allocate map.config.");
        return (1);
    }
    i = 0;
    while (i < N_CONFIGS + 1)
    {
        data->map.config[i] = NULL;
        i++;
    }
    return (0);
}

int init_map_ids_array(t_data *data)
{
    data->map.map_ids = malloc((N_CONFIGS + 1) * sizeof(char *));
    if (!data->map.map_ids)
    {
        error("Error: Failed to allocate map.map_ids.");
        free(data->map.config);
        return (1);
    }
    return (0);
}

void set_map_ids(t_data *data)
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

int init_ids(t_data *data)
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

int	contains_invalid_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!member_of_set(line[i], VALID_MAP_CHARS))
				return (1);
		i++;
	}
	return (0);
}

// first pull map data into a single string
int	parse_map(t_data *data, char *line)
{
	char	*temp;
	int		len;

	if (contains_invalid_char(line))
		return (1);
	temp = ft_strdup(data->map.flat_map);
	if (!temp) {
		error("Error: Memory allocation failed in ft_strdup.");
		return (1);
	}
	free(data->map.flat_map);
	data->map.flat_map = ft_strjoin(temp, line);
	free(temp);
	if (!data->map.flat_map) {
		error("Error: Memory allocation failed in ft_strjoin.");
		return (1);
	}
	len = ft_strlen(line); 
	if (len > data->map.width)
		data->map.width = len;
	data->map.height++;
	return (0);
}

int	print_array(char **arr)
{
	for (int i = 0; i < array_len(arr); i++)
		printf("%s\n", arr[i]);
	return (0);
}

int	no_valid_id(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (data->map.map_ids[i])
	{
		if (ft_strnstr(line, data->map.map_ids[i],
				ft_strlen(data->map.map_ids[i])))
			return (0);
		i++;
	}
	return (1);
}

int load_map_data(t_data *data, char *f_name)
{
    int fd;

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
        error("Error: Bad configuration file.");
    }
    
    load_map_clean_up(data, NULL, fd);
    debug_print_map(data);
    
    return (0);
}
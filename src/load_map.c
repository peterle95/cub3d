/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:41 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 15:09:39 by pmolzer          ###   ########.fr       */
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

// split each line and append to map.config
// parse_map() appends line to row in map.map_array
int verify_config_entry(t_data *data, char **config_entry)
{
    if (!config_entry)
        return (1);
    if (array_len(config_entry) != 2)
    {
        printf("no texture path...map.id: %d\n", data->map.id);
        return (1);
    }
    return (0);
}

int process_config_path(t_data *data)
{
    char *cpy;
    
    cpy = ft_strdup(data->map.config[data->map.id][1]);
    if (!cpy)
        return (1);
        
    free(data->map.config[data->map.id][1]);
    data->map.config[data->map.id][1] = ft_strtrim(cpy, "\n");
    free(cpy);
    
    if (!data->map.config[data->map.id][1])
        return (1);
        
    return (0);
}

int check_valid_map_id(t_data *data)
{
    int i;
    
    i = 0;
    while (data->map.map_ids[i])
    {
        if (ft_strncmp(data->map.config[data->map.id][0], 
                       data->map.map_ids[i],
                       ft_strlen(data->map.map_ids[i]) + 1) == 0)
        {
            data->map.id++;
            return (0);
        }
        i++;
    }
    return (1);
}

int process_config_line(t_data *data, char *line)
{
    data->map.config[data->map.id] = ft_split(line, ' ');
    
    if (verify_config_entry(data, data->map.config[data->map.id]))
        return (free_map_data(data));
        
    if (process_config_path(data))
        return (free_map_data(data));
        
    if (check_valid_map_id(data))
        return (free_map_data(data));
        
    return (0);
}

int parse_line(t_data *data, char *line)
{
    if (line[0] == '\0' || line[0] == '\n')
        return (0);
        
    if (no_valid_id(data, line))
        return (parse_map(data, line));
        
    return (process_config_line(data, line));
}

int	copy_chars(t_data *data, char *flat_map)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (*flat_map)
	{
		if (*flat_map == '\n')
		{
			i++;
			flat_map++;
			j = 0;
		}
		if (*flat_map)
		{
			data->map.map_array[i][j] = *flat_map;
			flat_map++;
			j++;
		}
	}
	return (0);
}

int allocate_map_array(t_data *data)
{
    data->map.map_array = malloc((data->map.height + 1) * sizeof(char *));
    if (!data->map.map_array)
    {
        error("Error: Failed to allocate map.array.");
        return (1);
    }
    data->map.map_array[data->map.height] = NULL;
    return (0);
}

int allocate_and_init_row(t_data *data, int row)
{
    int j;

    data->map.map_array[row] = ft_calloc(data->map.width + 1, sizeof(char));
    if (!data->map.map_array[row])
        return (1);
    
    j = 0;
    while (j < data->map.width)
    {
        data->map.map_array[row][j] = ' ';
        j++;
    }
    return (0);
}

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
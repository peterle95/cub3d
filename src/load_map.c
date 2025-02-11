/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:41 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/07 12:56:43 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// TODO: error handling for malloc fail
static int	init_ids(t_data *data)
{
	int	i;

	data->map.flat_map = ft_strdup("");
	// error
	data->map.width = 0;
	data->map.height = 0;
	data->map.config = malloc((N_CONFIGS + 1) * sizeof(char **));
	// error
	i = 0;
	while (i < N_CONFIGS + 1)
	{
		data->map.config[i] = NULL;
		i++;
	}
	data->map.map_ids = malloc((N_CONFIGS + 1) * sizeof(char *));
	// error
	data->map.map_ids[0] = "NO";
	data->map.map_ids[1] = "SO";
	data->map.map_ids[2] = "WE";
	data->map.map_ids[3] = "EA";
	data->map.map_ids[4] = "CE";
	data->map.map_ids[5] = "F";
	data->map.map_ids[6] = "C";
	data->map.map_ids[N_CONFIGS] = NULL;
	data->map.id = 0;
	return (0);	
}

static int	contains_invalid_char(char *line)
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
static int	parse_map(t_data *data, char *line)
{
	char	*temp;
	int		len;

	if (contains_invalid_char(line))
		return (1);
	temp = ft_strdup(data->map.flat_map);
	free(data->map.flat_map);
	data->map.flat_map = ft_strjoin(temp, line);
	free(temp);
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
static int	parse_line(t_data *data, char *line)
{
	if (line[0] == '\0' || line[0] == '\n')
		return (0);
	if (no_valid_id(data, line))
		return (parse_map(data, line));
	data->map.config[data->map.id] = ft_split(line, ' ');
	//error
	if (array_len(data->map.config[data->map.id]) != 2)
	{
		printf("no texture path...map.id: %d\n", data->map.id);
		return (free_map_data(data));
	}
	char *cpy = ft_strdup(data->map.config[data->map.id][1]);
	free(data->map.config[data->map.id][1]);
	data->map.config[data->map.id][1] = ft_strtrim(cpy, "\n");
	printf("\n%s::::::::::%d::::::::::%s\n\n",
			data->map.config[data->map.id][0],
			data->map.id, data->map.config[data->map.id][1]);
	free(cpy);
	int	i;
	i = 0;
	while (data->map.map_ids[i])
	{
		if (ft_strncmp(data->map.config[data->map.id][0], data->map.map_ids[i],
					ft_strlen(data->map.map_ids[i]) + 1) == 0)
		{
			data->map.id++;
			return(0);
		}
		i++;
	}
	printf("didn't load all configs or N_CONFIGS is wrong\n");
	return (free_map_data(data));
}

static int	copy_chars(t_data *data, char *flat_map)
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

// TODO: on error free flat_map
// load data->map.flat_map into data->map.map_array
static int	flat_map_to_map_array(t_data *data)
{
	int	i;
	int	j;

	if (DEBUG)
		printf("flat_map:\n%s", data->map.flat_map);
	data->map.map_array = malloc((data->map.height + 1) * sizeof(char *));
	data->map.map_array[data->map.height] = NULL;
	// error
	i = 0;
	j = 0;
	while (i < data->map.height)
	{
		data->map.map_array[i] = ft_calloc(data->map.width + 1, sizeof(char));
		// error
		j = 0;
		while (j < data->map.width)
		{
			data->map.map_array[i][j] = ' ';
			j++;
		}
		i++;
	}
	data->map.height = data->map.height;
	if (copy_chars(data, data->map.flat_map))
			return (1);
	return (0);
}

static int	load_map_clean_up(t_data *data, char *line, int fd)
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

int	load_map_data(t_data *data, char *f_name)
{
	int		fd;
	char	*line;
	char	buff;

	init_ids(data);
	fd = open(f_name, O_RDONLY);
	if (read(fd, &buff, 1) < 1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	fd = open(f_name, O_RDONLY);
	// error
	line = get_next_line(fd);
	if (line && parse_line(data, line) != 0)
		return load_map_clean_up(data, line, fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && parse_line(data, line) != 0)
			return load_map_clean_up(data, line, fd);
	}
	if (flat_map_to_map_array(data))
		printf("Bad configuration file.\n");
	load_map_clean_up(data, line, fd);
	if (DEBUG)
	{
		printf("map_array:\n");
		print_string_array(data->map.map_array, data->map.height);
	}
	return (0);
}

#include "window.h"

// add to free funcs
static int	init_ids(t_data *data)
{
	int	i;

	data->map.flat_map = ft_strdup("");
	data->map.n_rows = 0;
	data->map.width = 0;
	data->map.height = 0;
	data->map.texture_paths = malloc(N_TEXTURE_PATHS * sizeof(char **));
	// error
	i = 0;
	while (i < N_TEXTURE_PATHS)
	{
		data->map.texture_paths[i] = NULL;
		i++;
	}
	data->map.map_ids = malloc(N_TEXTURE_PATHS * sizeof(char *));
	// error
	data->map.map_ids[0] = "NO";
	data->map.map_ids[1] = "SO";
	data->map.map_ids[2] = "WE";
	data->map.map_ids[3] = "EA";
	data->map.map_ids[4] = "F";
	data->map.map_ids[5] = "C";
	data->map.map_ids[N_TEXTURE_PATHS - 1] = NULL;
	data->map.id = 0;
	return (0);	
}

static int	parse_map(t_data *data, char *line)
{
	int	len;
	data->map.flat_map = ft_strjoin(data->map.flat_map, line);
	len = ft_strlen(line); 
	if (len > data->map.width)
		data->map.width = len;
	data->map.n_rows++;
	return (0);
}

// split each line and append to 
// 	data->map.texture_paths
// 	data->floor
// 	data->ceiling
// parse_map() appends line to row in
// 	data->map.map_array
static int	parse_line(t_data *data, char *line)
{
	if (line[0] == '\0'|| line[0] == '\n')
		return (0);
	if (data->map.id > N_TEXTURE_PATHS - 2)
		return (parse_map(data, line));
	data->map.texture_paths[data->map.id] = ft_split(line, ' ');
	//error
	if (array_len(data->map.texture_paths[data->map.id]) != 2)
		return (free_map_data(data));
	if (ft_strncmp(data->map.texture_paths[data->map.id][0], data->map.map_ids[data->map.id],
				ft_strlen(data->map.map_ids[data->map.id]) + 1) == 0)
	{
		if (DEBUG)
		{
			int i = 0;
			while (data->map.texture_paths[data->map.id][i])
			{
				printf(":::::%s", data->map.texture_paths[data->map.id][i]);
					i++;
			}	
		}
		data->map.id++;
		return (0);
	}
	return (free_map_data(data));
}

static void	copy_chars(t_data *data, char *flat_map)
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
		if (*flat_map == ' ')
		{
			j++;
			flat_map++;
		}
		else if (member_of_set(*flat_map, VALID_MAP_CHARS))
		{
			data->map.map_array[i][j] = *flat_map;
			flat_map++;
			j++;
		}		
	}
}

// load data->map.flat_map into data->map.map_array
static int	flat_map_to_map_array(t_data *data)
{
	int	i;
	int	j;

	if (DEBUG)
		printf("flat_map:\n%s", data->map.flat_map);
	data->map.map_array = malloc(data->map.n_rows * sizeof(char *));
	// error
	i = 0;
	j = 0;
	while (i < data->map.n_rows)
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
	copy_chars(data, data->map.flat_map);
	return (0);
}

static int	load_map_clean_up(char *line, int fd)
{
	while (line)
	{
		free(line);
		get_next_line(fd);
	}
	close(fd);
	return(-1);
}

int	load_map_data(t_data *data, char *f_name)
{
	int		fd;
	char	*line;

	init_ids(data);
	fd = open(f_name, O_RDONLY);
	line = get_next_line(fd);
	if (line && parse_line(data, line) != 0)
		return load_map_clean_up(line, fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && parse_line(data, line) != 0)
			return load_map_clean_up(line, fd);
	}
	load_map_clean_up(line, fd);
	flat_map_to_map_array(data);
	// add freeing of flat array to load_map_clean_up
	if (DEBUG)
	{
		printf("map_array:\n");
		print_string_array(data->map.map_array, data->map.n_rows);
	}
	return (0);
}


// check for ids in specific order /
// exit if ids not present or if no path
// 		in case of C and F if no colour value
// parse map to array
// use depth first/flood fill algo search to check for holes
// if bonus check for spawn location
//



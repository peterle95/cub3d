#include "window.h"

char *get_next_line(int fd)
{
	fd = 0;
	fd++;
	return (0);
}


// add to free funcs
static int	init_ids(t_data *data)
{
	data->map.no = NULL;
	data->map.so = NULL;
	data->map.we = NULL;
	data->map.ea = NULL;
	data->map.map_ids = ft_calloc(7, sizeof(char *));
	// error
	data->map.map_ids[0] = "NO";
	data->map.map_ids[1] = "SO";
	data->map.map_ids[2] = "WE";
	data->map.map_ids[3] = "EA";
	data->map.map_ids[4] = "F";
	data->map.map_ids[5] = "C";
	data->map.map_ids[6] = NULL;
	data->map.id = 0;
	data->map.n = 3;
	return (0);	
}

static int	parse_line(t_data *data, char *line)
{
	char	**temp;
	int		i;
	
	if (line)
	{
		temp = ft_split(line, ' ');
		// error
		if (data->map.map_ids[data->map.id]
				&& ft_strncmp(data->map.map_ids[data->map.id], temp[0], 2) == 0)
		{
			i = 0;
			while  (temp[i])
			{
				printf("%s\n", temp[i]);
				i++;
			}
			data->map.id++;
		}	
	}
	// actually append to struct or array for internal processing
	// free strings in temp
	// free temp
	return (0);
}

int	load_map_data(t_data *data, char *f_name)
{
	int		fd;
	char	*line;

	init_ids(data);
	if (!validate_map(data))
		return (error("Invalid map configuration"));
	fd = open(f_name, O_RDONLY);
	line = get_next_line(fd);
	if (line)
		parse_line(data, line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		parse_line(data, line);
	}
	free(line);
	close(fd);
	return (0);
}

// check for ids in specific order /
// exit if ids not present or if no path
// 		in case of C and F if no colour value
// parse map to array
// use depth first/flood fill algo search to check for holes
// if bonus check for spawn location
//



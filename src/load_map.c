#include "window.h"

// add to free funcs
static int	init_ids(t_data *data)
{

	data->map.no = NULL;
	data->map.so = NULL;
	data->map.we = NULL;
	data->map.ea = NULL;
	
	data->map.texture_paths = malloc(7 * sizeof(char **));
	// error

	data->map.map_ids = malloc(7 * sizeof(char *));
	// error
	data->map.map_ids[0] = "NO";
	data->map.map_ids[1] = "SO";
	data->map.map_ids[2] = "WE";
	data->map.map_ids[3] = "EA";
	data->map.map_ids[4] = "F";
	data->map.map_ids[5] = "C";
	data->map.map_ids[6] = NULL;
	data->map.id = 0;
	return (0);	
}

// rule for map data
static int	parse_line(t_data *data, char *line)
{

	if (line)
	{
		// if (data->map.map_ids > 5)
		// 	parse_map(data, line);
		data->map.texture_paths[data->map.id] = ft_split(line, ' ');
		//error
		if (!data->map.texture_paths[data->map.id][0][0])
			return (free_temp_return(data->map.texture_paths[data->map.id], 0));
		if (ft_strncmp(data->map.texture_paths[data->map.id][0], data->map.map_ids[data->map.id],
					ft_strlen(data->map.map_ids[data->map.id]) + 1))
		{
			data->map.id++;
			return (0);
		}
	}
		// if (data->map.map_ids[data->map.id][0]
		// 		&& ft_strncmp(data->map.map_ids[data->map.id][0], temp[0],
		// 		ft_strlen(data->map.map_ids[data->map.id][0])) == 0)
	// 	{
	// 		i = 0;
	// 		while  (temp[i])
	// 		{
	// 			// append_to_structure_in_data();
	// 			if (ft_strdup(temp[1]))
	// 			printf("%s\n", temp[i]);
	// 			i++;
	// 		}
	// 		data->map.id++;
	// 	}	
	// 	else
	// 		return(free_temp_return(temp, -1));
	// }
	// free_2d_char_arr(temp);
	return (0);
}


int	load_map_data(t_data *data, char *f_name)
{
	int		fd;
	char	*line;

	init_ids(data);
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



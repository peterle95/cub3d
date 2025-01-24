#include "window.h"

// must free all elements in data->map.texture_paths
// which is a 3d char * array
int	free_temp_return(char **temp, int r)
{
	free_2d_char_arr(temp);
	return (r);
}

// int	parse_map(t_data *data, char *line)
// {
// 		
// }

//array { "NO", *"./path_to_texure"}

#include "window.h"

bool	member_of_set(char c, char *set)
{
    while (*set) 
	{
        if (*set == c) {
            return true;
        }
        set++;
    }
    return false;
}

int	array_len(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

int	free_map_data(t_data *data)
{
	int	i;
	int	j;

	// free map.map_ids
	free(data->map.map_ids); // must free individually
	// free map.texture_paths
	i = 0;
	while (i < N_TEXTURE_PATHS)
	{
		if (data->map.texture_paths[i])
		{
			j = 0;
			while (data->map.texture_paths[i][j])
			{
				free(data->map.texture_paths[i][j]);
				j++;
			}
		}
		i++;
	}
	return (-1);
}


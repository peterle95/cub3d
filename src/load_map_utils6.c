/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_utils6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:12:17 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 16:54:34 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	if (!temp)
	{
		error("Memory allocation failed in ft_strdup", ENOMEM);
		return (1);
	}
	free(data->map.flat_map);
	data->map.flat_map = ft_strjoin(temp, line);
	free(temp);
	if (!data->map.flat_map)
	{
		error("Memory allocation failed in ft_strjoin", ENOMEM);
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
	int		i;

	i = 0;
	while (i < array_len(arr))
	{
		printf("%s\n", arr[i]);
		i++;
	}
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

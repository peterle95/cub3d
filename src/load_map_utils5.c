/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:13:20 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/18 13:26:10 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	duplicate(t_data *data, char *line)
{
	int		i;
	int		j;
	char	*substr;

	i = 0;
	while (data->map.map_ids[i])
	{
		substr = ft_strnstr(line, data->map.map_ids[i],
				ft_strlen(data->map.map_ids[i]));
		if (substr)
		{
			j = 0;
			while (data->map.config[j])
			{
				if (ft_strncmp(data->map.config[j][0], substr,
					ft_strlen(data->map.config[j][0])) == 0)
					return (1);
				j++;
			}
		}
		i++;
	}
	return (0);
}

int	parse_line(t_data *data, char *line)
{
	if (line[0] == '\0' || line[0] == '\n')
		return (0);
	if (data->fnbl == 0)
	{
		if (no_valid_id(data, line))
			return (1);
	}
	if (duplicate(data, line))
	{
		error("Duplicate texture", EINVAL);
		return (1);
	}
	if (no_valid_id(data, line))
		return (parse_map(data, line));
	return (process_config_line(data, line));
}

int	copy_chars(t_data *data, char *flat_map)
{
	int		i;
	int		j;

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

int	allocate_map_array(t_data *data)
{
	data->map.map_array = malloc((data->map.height + 1) * sizeof(char *));
	if (!data->map.map_array)
	{
		error("Failed to allocate map.array", ENOMEM);
		return (1);
	}
	data->map.map_array[data->map.height] = NULL;
	return (0);
}

int	allocate_and_init_row(t_data *data, int row)
{
	int		j;

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

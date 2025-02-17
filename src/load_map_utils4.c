/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:13:15 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/17 09:38:41 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	verify_config_entry(t_data *data, char **config_entry)
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

int	process_config_path(t_data *data)
{
	char	*cpy;

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

int	check_valid_map_id(t_data *data)
{
	int		i;

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

int	process_config_line(t_data *data, char *line)
{
	char	**config_entry;

	config_entry = ft_split(line, ' ');
	if (verify_config_entry(data, config_entry))
	{
		free_split(config_entry);
		return (1);
	}
	data->map.config[data->map.id] = config_entry;
	if (process_config_path(data))
	{
		free_split(config_entry);
		return (1);
	}
	if (check_valid_map_id(data))
	{
		free_split(config_entry);
		return (1);
	}
	return (0);
}

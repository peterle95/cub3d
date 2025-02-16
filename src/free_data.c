/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:11 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/16 23:56:59 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_and_terminate(t_data data, char *msg)
{
	error(msg, EINVAL);
	terminator(&data, EXIT_FAILURE);
}

static void	free_map_config(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (data->map.config)
	{
		while (i < N_CONFIGS)
		{
			if (data->map.config[i])
			{
				j = 0;
				while (data->map.config[i][j])
				{
					free(data->map.config[i][j]);
					j++;
				}
				free(data->map.config[i]);
			}
			i++;
		}
		free(data->map.config);
		data->map.config = NULL;
	}
}

int	free_data(t_data *data)
{
	if (data->map.map_ids)
	{
		free(data->map.map_ids);
		data->map.map_ids = NULL;
	}
	if (data->map.flat_map)
		free(data->map.flat_map);
	free_map_config(data);
	free_2d_char_arr(data->map.map_array);
	return (-1);
}

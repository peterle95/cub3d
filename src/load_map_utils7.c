/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_utils7.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:28:22 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 15:29:12 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	init_flat_map(t_data *data)
{
	data->map.flat_map = ft_strdup("");
	if (!data->map.flat_map)
	{
		error("Failed to allocate flat_map", errno);
		return (1);
	}
	return (0);
}

int	init_config(t_data *data)
{
	int		i;

	data->map.config = malloc((N_CONFIGS + 1) * sizeof(char **));
	if (!data->map.config)
	{
		error("Failed to allocate map.config", errno);
		return (1);
	}
	i = 0;
	while (i < N_CONFIGS + 1)
	{
		data->map.config[i] = NULL;
		i++;
	}
	return (0);
}

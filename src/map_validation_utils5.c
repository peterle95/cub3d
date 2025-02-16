/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:26:06 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/16 11:41:25 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_player_cell(char **map, const int dims[2], int i, int j)
{
	if (i == 0 || i == dims[0] - 1 || j == 0 || j == dims[1] - 1)
	{
		printf("Error: Player is on border of map at [%d][%d]\n", i, j);
		return (1);
	}
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
		map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
	{
		printf("Error: Player not enclosed by walls at [%d][%d]\n", i, j);
		return (1);
	}
	return (0);
}

int	validate_player_inside_map(char **map, int height, int width)
{
	int		i;
	int		j;
	int		dims[2];

	dims[0] = height;
	dims[1] = width;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (is_player_position(map[i][j]))
			{
				if (validate_player_cell(map, dims, i, j))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

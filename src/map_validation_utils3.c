/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:10:49 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:18:05 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_right(char **map, int i, int j)
{
	if (!(map[i][j + 1]) || map[i][j + 1] == ' ')
	{
		printf("Error: Map not closed at position [%d][%d] (right)\n", i, j);
		return (1);
	}
	return (0);
}

int	is_surrounded_by_walls(char **map, int height, int width)
{
	int		i;
	int		j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width && map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (check_top(map, i, j) || check_bottom(map, i, j, height)
					|| check_left(map, i, j) || check_right(map, i, j))
					return (1);
			}
		}
	}
	return (0);
}

int	process_row(char *row, char *valid_chars, int *player_count)
{
	int		j;

	j = -1;
	while (row[++j])
	{
		if (!ft_strchr(valid_chars, row[j]))
		{
			error("Error: Invalid character in map", EINVAL);
			return (1);
		}
		if (ft_strchr(VALID_PLAYER_CHARS, row[j]))
			(*player_count)++;
	}
	return (0);
}

int	check_player_count(int count)
{
	if (count != 1)
	{
		error("Error: There must be exactly one player in the map", EINVAL);
		return (1);
	}
	return (0);
}

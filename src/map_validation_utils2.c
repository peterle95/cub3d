/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:11:02 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_rgb(const char *color, unsigned int rgb[3])
{
	char	**values;
	int		result;

	values = ft_split(color, ',');
	if (!values)
		return (1);
	result = process_rgb_values(values, rgb);
	free_split(values);
	return (result);
}

int	check_top(char **map, int i, int j)
{
	size_t	line_len;

	if (i == 0)
	{
		printf("Error: Map not closed at position [%d][%d] (top)\n", i, j);
		return (1);
	}
	line_len = ft_strlen(map[i - 1]);
	if (!map[i - 1][j] || ((size_t)j >= line_len) || map[i - 1][j] == ' ')
	{
		printf("Error: Map not closed at position [%d][%d] (top)\n", i, j);
		return (1);
	}
	return (0);
}

int	check_bottom(char **map, int i, int j, int height)
{
	size_t	line_len;

	if (i == height - 1)
	{
		printf("Error: Map not closed at position [%d][%d] (bottom)\n", i, j);
		return (1);
	}
	line_len = ft_strlen(map[i + 1]);
	if (!map[i + 1][j] || ((size_t)j >= line_len) || map[i + 1][j] == ' ')
	{
		printf("Error: Map not closed at position [%d][%d] (bottom)\n", i, j);
		return (1);
	}
	return (0);
}

int	check_left(char **map, int i, int j)
{
	if (j == 0 || map[i][j - 1] == ' ')
	{
		printf("Error: Map not closed at position [%d][%d] (left)\n", i, j);
		return (1);
	}
	return (0);
}

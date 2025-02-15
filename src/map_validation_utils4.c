/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:16:07 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map_chars(char **map, char *valid_chars)
{
	int		i;
	int		player_count;

	player_count = 0;
	i = -1;
	while (map[++i])
	{
		if (process_row(map[i], valid_chars, &player_count))
			return (1);
	}
	return (check_player_count(player_count));
}

int	try_path_with_prefix(char *path, char *prefix)
{
	char	*full_path;
	int		fd;

	full_path = ft_strjoin(prefix, path);
	if (!full_path)
		return (0);
	fd = open(full_path, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		free(full_path);
		return (1);
	}
	free(full_path);
	return (0);
}

int	validate_texture_path(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	if (try_path_with_prefix(path, "src/"))
		return (1);
	if (try_path_with_prefix(path, "./"))
		return (1);
	return (0);
}

int	validate_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < N_TEXTURES - 2)
	{
		if (data->map.config[i]
			&& ft_strncmp(data->map.config[i][0], "F", 2) != 0
				&& ft_strncmp(data->map.config[i][0], "C", 2) != 0)
		{
			if (!validate_texture_path(data->map.config[i][1]))
				return (-1);
		}
		i++;
	}
	return (0);
}

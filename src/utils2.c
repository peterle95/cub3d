/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:58:26 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:08:09 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	has_cub_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(&filename[len - 4], ".cub", 4) == 0)
		return (1);
	return (0);
}

// Function to handle window close event
int	close_window(t_data *data)
{
	if (data->textures.img[0].ptr)
		mlx_destroy_image(data->mlx, data->textures.img[0].ptr);
	if (data->img_data0->img)
		mlx_destroy_image(data->mlx, data->img_data0->img);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
	return (0);
}

int	return_bad_texture(char *id, char *path)
{
	printf("Failed to load texture %s at path %s\n", id, path);
	return (0);
}

int	return_bad_image(t_data *data, int index, char *id)
{
	printf("Error: Failed to get texture data address for %s\n", id);
	mlx_destroy_image(data->mlx, data->textures.img[index].ptr);
	return (0);
}

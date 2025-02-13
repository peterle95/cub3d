/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:57:11 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 17:39:31 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// oder of mlx_destroy funcs important
// afrer calling mlx_destroy_image() can
// then free mem allocated for struct t_img_data
int	terminator(t_data *data)
{
	printf("Hasta la vista, baby!\n");
	free_data(data);
	mlx_destroy_image(data->mlx, data->img_data0->img);
	free(data->img_data0);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	init_colour_fade(t_data *data)
{
	data->t = 0;
	data->r = 255;
	data->g = 0;
	data->b = 0;
}

int	set_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	free_2d_char_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

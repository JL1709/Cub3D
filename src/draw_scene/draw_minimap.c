/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:45:06 by jludt             #+#    #+#             */
/*   Updated: 2021/11/14 18:57:59 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

extern int	worldMap[MAP_WIDTH][MAP_HEIGHT];

static void	draw_background(t_data *data)
{
	int		i;
	int		j;
	int		color;

	color = create_trgb(0, 128, 128, 128);
	i = -1;
	while (++i < MAP_WIDTH *  5)
	{
		j = -1;
		while (++j < MAP_HEIGHT * 5)
			my_mlx_pixel_put(data, i, j, color);
	}
}

static void	draw_map(t_data *data)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		color;

	color = create_trgb(0, 255, 255, 255);
	y = -1;
	while (++y < MAP_HEIGHT)
	{
		x = -1;
		while (++x < MAP_WIDTH)
		{
			if (worldMap[y][x] > 0)
			{
				i = 0;
				while (++i < 5)
				{
					j = 0;
					while (++j < 5)
						my_mlx_pixel_put(data, (x * 5) + i, (y * 5) + j, color);
				}
			}
		}
	}
}

// static void	draw_player(t_data *data)
// {
// 	float		x;
// 	float		y;
// 	int		color;

// 	color = create_trgb(0, 255, 0, 0);
// 	x = data->posX + (SCREEN_WIDTH / MAP_WIDTH);
// 	while (x < (SCREEN_WIDTH / MAP_WIDTH) + data->posX + 3)
// 	{
// 		y = (SCREEN_HEIGHT / MAP_HEIGHT) + data->posY;
// 		while (y < (SCREEN_HEIGHT / MAP_HEIGHT) + data->posY + 3)
// 		{
// 			my_mlx_pixel_put(data, x, y, color);
// 			y++;
// 		}
// 		x++;
// 	}
// }

void	draw_minimap(t_data *data)
{
	draw_background(data);
	draw_map(data);
	// draw_player(data);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0001/08/11 11:16:07 by jludt             #+#    #+#             */
/*   Updated: 2021/11/15 13:36:59 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// just for test cases -> needs to be done the right way -> see pdf for instructions
int map[24][24] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	init(t_data *data)
{
	data->player.map_pos_x = 10;
	data->player.map_pos_y = 7;
	data->grid_size = HEIGHT / data->player.map_pos_y;
	data->speed = data->grid_size / 2;
	data->player.side = NORTH;
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img->addr + (y * data->img->line_length
			+ x * (data->img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_data *data, int x1, int y1, int x2, int y2)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	x = x1;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	while (x < x2)
	{
		y = y1 + dy * (x - x1) / dx;
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
		x++;
	}
}

int	keys_hooks(int key, t_data *data)
{
	if (key == ESC_KEY)
		exit(0);
	return (0);	
}

void	init_projection_plane(t_data *data)
{
	if (data->player.side == NORTH)
		data->dst_to_projection_plane = data->player.map_pos_y;
	else if (data->player.side == SOUTH)
		data->dst_to_projection_plane = 24 - data->player.map_pos_y;
	else if (data->player.side == WEST)
		data->dst_to_projection_plane = data->player.map_pos_x;
	else
		data->dst_to_projection_plane = 24 - data->player.map_pos_x;
	data->projection_plane_width = 2 * (data->dst_to_projection_plane * tan(30 * rad));
	data->grid_size = data->player.map_pos_x - data->projection_plane_width / 2;;
}

void	start_game(t_data *data)
{
	int		w;				/* screen width */
	bool	hit;			/* is wall in grid */
	double	map_x;
	double	x_dist;			/* distace to wall in x coordinate */
	double	y_dist;			/* distace to wall in y coordinate */
	double	grids_in_pixel; /* number of grids in one pixel*/

	w = 0;
	init_projection_plane(data);
	grids_in_pixel = data->projection_plane_width / WIDTH;
	map_x = data->player.map_pos_x - data->projection_plane_width / 2;
	while (w < WIDTH)
	{
		hit = 0;
		while (hit == 0)
		{
			get_dist(data->player.map_pos_x, data->player.map_pos_x, map_x, 0);
		}
		w++;
		map_x += grids_in_pixel;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->img = (t_img *)malloc(sizeof(t_img));

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	data->img->ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	init(data);
	start_game(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->ptr, 0, 0);
	mlx_hook(data->win, 0, 0, keys_hooks, data);
	mlx_loop(data->mlx);
	return (0);
}

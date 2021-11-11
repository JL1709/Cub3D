/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 11:16:27 by jludt             #+#    #+#             */
/*   Updated: 2021/11/10 22:52:59 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	game_on(t_data *data)
{
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, screenWidth, screenHeight);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.sl, &data->img.endian);
	drawWindowGray(data);
	drawMap(data);
	drawPlayer(data);
	drawRays2D(data);
	drawDirection(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.img_ptr, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	
	(void)	argc;
	(void)	**argv;

	initialize_map(&data);
	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, screenWidth, screenHeight, "Cub3d");
	mlx_loop_hook(data.mlx_ptr, game_on, &data);
	mlx_hook(data.mlx_win, 2, 1L << 0, interactive, &data);
	mlx_loop(data.mlx_ptr);

	//free_data(data) -> needs to be done
	return (0);
}


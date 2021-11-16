/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:46:19 by jludt             #+#    #+#             */
/*   Updated: 2021/11/16 17:17:57 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int worldMap[MAP_WIDTH][MAP_HEIGHT]=
{
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,2,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,0,3},
	{3,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,3},
	{3,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,2,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
};

void	initialize_map(t_data *data)
{	
	data->posX = 10.5;
	data->posY = 1.5;
	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = 0.66;
	data->moveSpeed = 0.05;
	data->rotSpeed = 0.05;
	load_texture(data);
}

void	load_texture(t_data *data)
{
	t_img	img;

	load_image(data, data->texture[0], "textures/eagle.xpm", &img);
	load_image(data, data->texture[1], "textures/redbrick.xpm", &img);
	load_image(data, data->texture[2], "textures/purplestone.xpm", &img);
	load_image(data, data->texture[3], "textures/greystone.xpm", &img);
	load_image(data, data->texture[4], "textures/bluestone.xpm", &img);
	load_image(data, data->texture[5], "textures/mossy.xpm", &img);
	load_image(data, data->texture[6], "textures/wood.xpm", &img);
	load_image(data, data->texture[7], "textures/colorstone.xpm", &img);
}

void	load_image(t_data *data, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;
	
	img->img = mlx_xpm_file_to_image(data->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			texture[img->img_height * y + x] = img->data[img->img_height * y + x];
	}
	mlx_destroy_image(data->mlx, img->img);
}

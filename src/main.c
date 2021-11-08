/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 11:16:27 by jludt             #+#    #+#             */
/*   Updated: 2021/11/08 10:45:54 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


// just for test cases -> needs to be done the right way -> see pdf for instructions
int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


// int	game_on(t_data *data)
// {
// 	int		x;
// 	double	deltaDistX;
// 	double	deltaDistY;
// 	double posX = 22, posY = 12;  //x and y start position
// 	double dirX = -1, dirY = 0; //initial direction vector
// 	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

// 	data->blue = 0x6F;

// 	double time = 0; //time of current frame
// 	double oldTime = 0; //time of previous frame
	
// 	data->mlx_img = mlx_new_image(data->mlx, screenWidth, screenHeight);
// 	data->mlx_data_addr = mlx_get_data_addr(data->mlx_img, &data->mlx_bits_per_pixel, \
// 						&data->mlx_size_line, &data->mlx_endian);
	
// 	x = -1;
// 	while (++x < screenWidth)
// 	{
// 		//calculate ray position and direction
// 		double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
// 		double rayDirX = dirX + planeX * cameraX;
// 		double rayDirY = dirY + planeY * cameraX;
// 		//which box of the map we're in
// 		int mapX = (int)posX;
// 		int mapY = (int)posY;

// 		//length of ray from current position to next x or y-side
// 		double sideDistX;
// 		double sideDistY;
		
// 		deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
// 		deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);

// 		double perpWallDist;

// 		//what direction to step in x or y-direction (either +1 or -1)
// 		int stepX;
// 		int stepY;

// 		int hit = 0; //was there a wall hit?
// 		int side; //was a NS or a EW wall hit?
// 		//calculate step and initial sideDist
// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (posX - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
// 		}
// 		if(rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (posY - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
// 		}
// 		//perform DDA
// 		while (hit == 0)
// 		{
// 			//jump to next map square, either in x-direction, or in y-direction
// 			if(sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			//Check if ray has hit a wall
// 			if (worldMap[mapX][mapY] > 0)
// 				hit = 1;
// 		}
// 		if (side == 0) 
// 			perpWallDist = (sideDistX - deltaDistX);
// 		else
// 			perpWallDist = (sideDistY - deltaDistY);
		
// 		//Calculate height of line to draw on screen
// 		int lineHeight = (int)(screenHeight / perpWallDist);

// 		//calculate lowest and highest pixel to fill in current stripe
// 		int drawStart = -lineHeight / 2 + screenHeight / 2;
// 		if (drawStart < 0) 
// 			drawStart = 0;
// 		int drawEnd = lineHeight / 2 + screenHeight / 2;
// 		if (drawEnd >= screenHeight)
// 			drawEnd = screenHeight - 1;

// 		offset = y * data->mlx_size_line + x * (data->mlx_bits_per_pixel / 8);
// 		data->mlx_data_addr[offset] = data->blue;
		
// 	}
	
// 	mlx_put_image_to_window(data->mlx, data->mlx_win, data->mlx_img, 0, 0);
// 	// print_usage(data); -> needs to be done if necessary
// 	mlx_destroy_image(data->mlx, data->mlx_img);
	
// }



int	main(int argc, char *argv[])
{
	t_data	*data;
	
	(void)	argc;
	(void)	**argv;

	// error management needs to be done
	// getting input the right way needs to be done

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (0);
	
	data->relative_path = "./images/Box_Wall.xpm";
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, screenWidth, screenHeight, "Cub3d");
	data->mlx_img = mlx_xpm_file_to_image(data->mlx, data->relative_path, &data->mlx_img_width, &data->mlx_img_height);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->mlx_img, 0, 0);
	//mlx_loop_hook(data->mlx, game_on, data);
	mlx_loop(data->mlx);

	//free_data(data) -> needs to be done
	return (0);
}


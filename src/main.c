/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 11:16:27 by jludt             #+#    #+#             */
/*   Updated: 2021/11/11 16:41:58 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx_data_addr + (y * data->mlx_size_line + x * (data->mlx_bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	game_on(t_data *data)
{
	int		x;
	// double	time = 0; //time of current frame
	// double	oldTime = 0; //time of previous frame

	double cameraX;
	double rayDirX;
	double rayDirY;

	//which box of the map we're in
	int	mapX;
	int	mapY;

	//length of ray from current position to next x or y-side
	double	sideDistX;
	double	sideDistY;

	//length of ray from one x or y-side to next x or y-side
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;

	//what direction to step in x or y-direction (either +1 or -1)
	int	stepX;
	int	stepY;

	int	hit; //was there a wall hit?
	int	side; //was a NS or a EW wall hit?

	//Calculate height of line to draw on screen
	int	lineHeight;

	//calculate lowest and highest pixel to fill in current stripe
	int	drawStart;
	int	drawEnd;

	int		color;
	
	data->mlx_img = mlx_new_image(data->mlx, screenWidth, screenHeight);
		
	x = -1;
	while (++x < screenWidth)
	{
		//calculate ray position and direction
		cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		rayDirX = data->dirX + data->planeX * cameraX;
		rayDirY = data->dirY + data->planeY * cameraX;
		
		//which box of the map we're in
		mapX = (int)data->posX;
		mapY = (int)data->posY;
		
		//length of ray from one x or y-side to next x or y-side
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		hit = 0; //was there a wall hit?
		
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
		}
		
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0) 
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		
		//Calculate height of line to draw on screen
		lineHeight = (int)(screenHeight / perpWallDist) * 3;

		//calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0) 
			drawStart = 0;
		drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		if (worldMap[mapX][mapY] == 1)
			color = create_trgb(0, 255, 0, 0);		//red
		else if (worldMap[mapX][mapY] == 2)
			color = create_trgb(0, 0, 255, 0);		//green
		else if (worldMap[mapX][mapY] == 3)
			color = create_trgb(0, 0, 0, 255);		//blue
		else if (worldMap[mapX][mapY] == 4)
			color = create_trgb(0, 255, 255, 255);	//white
		else
			color = create_trgb(0, 255, 255, 0);	//yellow
		if (side == 1)
			color = color / 2;
		
		data->mlx_data_addr = mlx_get_data_addr(data->mlx_img, &data->mlx_bits_per_pixel, \
						&data->mlx_size_line, &data->mlx_endian);
		while (drawStart < drawEnd)
		{
			my_mlx_pixel_put(data, x, drawStart, color);
			drawStart++;
		}
	}
	data->oldTime = data->time;
	data->time = get_time();
	data->frameTime = (data->time - data->oldTime) / 1000.0;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->mlx_img, 0, 0);
	mlx_destroy_image(data->mlx, data->mlx_img);
	return (0);
	
}

int	ft_close(t_data *data) // quit game when ESC is pressed
{
	(void)	*data;
	
	//free_data() //ToDO
	exit(0);
}

int	interactive(int key, t_data *data)
{	
	//speed modifiers
	double moveSpeed = data->frameTime * 5.0; //the constant value is in squares/second
	double rotSpeed = data->frameTime * 3.0; //the constant value is in radians/second
	
	if (key == KEY_ESCAPE) //free data befor exiting still to be done
		exit(0);
	else if (key == KEY_ANSI_W)			//move forward
	{
		if (worldMap[(int)(data->posX + data->dirX * moveSpeed)][(int)data->posY] == 0)
			data->posX += data->dirX * moveSpeed;
		if(worldMap[(int)data->posX][(int)(data->posY + data->dirY * moveSpeed)] == 0) 
			data->posY += data->dirY * moveSpeed;
	}
	else if (key == KEY_ANSI_S)			//move backwards
	{
		if (worldMap[(int)(data->posX + data->dirX * moveSpeed)][(int)data->posY] == 0)
			data->posX -= data->dirX * moveSpeed;
		if(worldMap[(int)data->posX][(int)(data->posY + data->dirY * moveSpeed)] == 0) 
			data->posY -= data->dirY * moveSpeed;
	}
	// else if (key == KEY_ANSI_A)			//move to the left
	// 	data->posY -= 0.2;
	// else if (key == KEY_ANSI_D)			//move to the right
	// 	data->posY += 0.2;
	else if (key == KEY_LEFTARROW)			//rotate to the left
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(rotSpeed) - data->dirY * sin(rotSpeed);
		data->dirY = oldDirX * sin(rotSpeed) + data->dirY * cos(rotSpeed);
		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(rotSpeed) - data->planeY * sin(rotSpeed);
		data->planeY = oldPlaneX * sin(rotSpeed) + data->planeY * cos(rotSpeed);
	}
	else if (key == KEY_RIGHTARROW)		//rotate to the right
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(-rotSpeed) - data->dirY * sin(-rotSpeed);
		data->dirY = oldDirX * sin(-rotSpeed) + data->dirY * cos(-rotSpeed);
		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(-rotSpeed) - data->planeY * sin(-rotSpeed);
		data->planeY = oldPlaneX * sin(-rotSpeed) + data->planeY * cos(-rotSpeed);
	}
	return (0);
}


void	initialize_map(t_data *data)
{	
	data->posX = 22;		//x start position
	data->posY = 12;		//y start position
	data->dirX = -1;		//initial direction vector
	data->dirY = 0;			//initial direction vector
	data->planeX = 0;
	data->planeY = 0.66;	//the 2d raycaster version of camera plane
	data->time = get_time();			//time of current frame
	data->oldTime = 0;		//time of previous frame
	data->frameTime = 0;	//frameTime is the time this frame has taken, in seconds
}

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

	//data->relative_path = "./images/Box_Wall.xpm";
	initialize_map(data);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, screenWidth, screenHeight, "Cub3d");
	mlx_loop_hook(data->mlx, game_on, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, interactive, data);
	mlx_hook(data->mlx_win, 17, 1L << 2, ft_close, data);
	mlx_loop(data->mlx);

	//free_data(data) -> needs to be done
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 11:16:27 by jludt             #+#    #+#             */
/*   Updated: 2021/11/09 21:14:09 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int worldMap[mapWidth][mapHeight]=
{
	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
	{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
	{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
	{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
	{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
	{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
	{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

unsigned int	buffer[screenHeight][screenWidth];

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
	int		y;
	// int		i;
	// int		j;
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

	//texturing calculations
	int texNum;

	//calculate value of wallX
	double	wallX; //where exactly the wall was hit

	//x coordinate on the texture
	int	texX;

	// How much to increase the texture coordinate per screen pixel
	double	step;

	// Starting texture coordinate
	double	texPos;

	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
	int texY;

	int	color;

	// generate some textures
	unsigned int	texture[8][texWidth * texHeight];
	int				xcolor;
	int				ycolor;
	int				xycolor;
	x = -1;
	while (++x < texWidth)
	{
		y = -1;
		while (++y < texHeight)
		{
			xcolor = x * 256 / texWidth;
			ycolor = x * 256 / texHeight;
			xycolor = y * 128 / texHeight + x * 128 / texWidth;
		    texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			texture[3][texWidth * y + x] = xcolor + 256 * xcolor + 65536 * xcolor; //xor greyscale
			texture[4][texWidth * y + x] = 256 * xcolor; //xor green
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}

	// load images
	// data->img = (t_img **)ft_calloc(9, sizeof(t_img *));

	// data->img[0] = (t_img *)malloc(sizeof(t_img));
	// data->img[0]->img_ptr = mlx_new_image(data->mlx_ptr, \
	// 	data->win.width, data->win.height);
	// data->img[0]->data_addr = mlx_get_data_addr(data->img[0]->img_ptr, &data->img[0]->bpp, 
	// 	&data->img[0]->size_line, &data->img[0]->endian);

	// data->img[1] = (t_img *)malloc(sizeof(t_img));
	// data->img[1]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	// 	IMG_BOX_WALL, &data->img[1]->width, &data->img[1]->height);
	// data->img[1]->data_addr = mlx_get_data_addr(data->img[1]->img_ptr, &data->img[1]->bpp, 
	// 	&data->img[1]->size_line, &data->img[1]->endian);

	// data->img[2] = (t_img *)malloc(sizeof(t_img));
	// data->img[2]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	// 	IMG_BOX_WALL, &data->img[2]->width, &data->img[2]->height);
	// data->img[2]->data_addr = mlx_get_data_addr(data->img[2]->img_ptr, &data->img[2]->bpp, 
	// 	&data->img[2]->size_line, &data->img[2]->endian);
		
	// data->img[3] = (t_img *)malloc(sizeof(t_img));
	// data->img[3]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	// 	IMG_BOX_WALL, &data->img[3]->width, &data->img[3]->height);
	// data->img[3]->data_addr = mlx_get_data_addr(data->img[3]->img_ptr, &data->img[3]->bpp, 
	// 	&data->img[3]->size_line, &data->img[3]->endian);

	// data->img[4] = (t_img *)malloc(sizeof(t_img));
	// data->img[4]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	// 	IMG_BOX_WALL, &data->img[4]->width, &data->img[4]->height);
	// data->img[4]->data_addr = mlx_get_data_addr(data->img[4]->img_ptr, &data->img[4]->bpp, 
	// 	&data->img[4]->size_line, &data->img[4]->endian);

	// data->img[5] = (t_img *)malloc(sizeof(t_img));
	// data->img[5]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	// 	IMG_BOX_WALL, &data->img[5]->width, &data->img[5]->height);
	// data->img[5]->data_addr = mlx_get_data_addr(data->img[5]->img_ptr, &data->img[5]->bpp, 
	// 	&data->img[5]->size_line, &data->img[5]->endian);

	// data->img[6] = (t_img *)malloc(sizeof(t_img));
	// data->img[6]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	// 	IMG_BOX_WALL, &data->img[6]->width, &data->img[6]->height);
	// data->img[6]->data_addr = mlx_get_data_addr(data->img[6]->img_ptr, &data->img[6]->bpp, 
	// 	&data->img[6]->size_line, &data->img[6]->endian);

	// data->img[7] = (t_img *)malloc(sizeof(t_img));
	// data->img[7]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	// 	IMG_BOX_WALL, &data->img[7]->width, &data->img[7]->height);
	// data->img[7]->data_addr = mlx_get_data_addr(data->img[7]->img_ptr, &data->img[7]->bpp, 
	// 	&data->img[7]->size_line, &data->img[7]->endian);

	// data->img[8] = (t_img *)malloc(sizeof(t_img));
	// data->img[8]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	// 	IMG_BOX_WALL, &data->img[8]->width, &data->img[8]->height);
	// data->img[8]->data_addr = mlx_get_data_addr(data->img[8]->img_ptr, &data->img[8]->bpp, 
	// 	&data->img[8]->size_line, &data->img[8]->endian);
	
	data->mlx_img = mlx_new_image(data->mlx_ptr, screenWidth, screenHeight);
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
		// deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		// deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
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
		if (rayDirY < 0)
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
	
		//texturing calculations
		texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		if (side == 0)
			wallX = data->posY + perpWallDist * rayDirY;
		else
			wallX = data->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
		data->mlx_data_addr = mlx_get_data_addr(data->mlx_img, &data->mlx_bits_per_pixel, \
						&data->mlx_size_line, &data->mlx_endian);
		y = drawStart;
		while (y < drawEnd)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			texY = (int)texPos & (texHeight - 1);
			texPos += step;
			color = texture[texNum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			printf("color = %i\n", color);
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->mlx_img, 0, 0);
	//mlx_destroy_image(data->mlx_ptr, data->mlx_img);
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
	if (key == KEY_ESCAPE) //free data befor exiting still to be done
		exit(0);
	else if (key == KEY_ANSI_A)			//move to the left
			data->posY -= 0.2;
	else if (key == KEY_ANSI_D)			//move to the right
		data->posY += 0.2;
	else if (key == KEY_ANSI_W)			//move forward
			data->posX -= 0.2;
	else if (key == KEY_ANSI_S)			//move backwards
			data->posX += 0.2;
	// else if (key == KEY_LEFTARROW)		//look/turn to the left
	// 	data->dirX -= 1;
	// else if (key == KEY_RIGHTARROW)		//look/turn to the right
	// 	data->dirX += 1;
	return (0);
}


void	initialize_map(t_data *data)
{	
	data->posX = 22;		//x start position
	data->posY = 11.5;		//y start position
	data->dirX = -1;		//initial direction vector
	data->dirY = 0;			//initial direction vector
	data->planeX = 0;
	data->planeY = 0.66;	//the 2d raycaster version of camera plane
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
	data->mlx_ptr = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx_ptr, screenWidth, screenHeight, "Cub3d");
	mlx_loop_hook(data->mlx_ptr, game_on, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, interactive, data);
	mlx_hook(data->mlx_win, 17, 1L << 2, ft_close, data);
	mlx_loop(data->mlx_ptr);

	//free_data(data) -> needs to be done
	return (0);
}


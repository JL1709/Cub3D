/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:56:25 by jludt             #+#    #+#             */
/*   Updated: 2021/11/17 14:19:37 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

extern int	worldMap[MAP_WIDTH][MAP_HEIGHT];

void	calc_initial_state(t_data *data, t_rc *rc)
{
	rc->cameraX = 2 * rc->x / (double)SCREEN_WIDTH - 1;
	rc->rayDirX = data->dirX + data->planeX * rc->cameraX;
	rc->rayDirY = data->dirY + data->planeY * rc->cameraX;
	rc->mapX = (int)data->posX;
	rc->mapY = (int)data->posY;
	rc->deltaDistX = fabs(1 / rc->rayDirX);
	rc->deltaDistY = fabs(1 / rc->rayDirY);
	rc->hit = 0;
}

void	calc_step_and_side_dist(t_data *data, t_rc *rc)
{
	if (rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideDistX = (data->posX - rc->mapX) * rc->deltaDistX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDistX = (rc->mapX + 1.0 - data->posX) * rc->deltaDistX;
	}
	if (rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideDistY = (data->posY - rc->mapY) * rc->deltaDistY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDistY = (rc->mapY + 1.0 - data->posY) * rc->deltaDistY;
	}
}

void	perform_dda(t_rc *rc, t_data *data)
{
	while (rc->hit == 0)
	{
		if (rc->sideDistX < rc->sideDistY)
		{
			rc->sideDistX += rc->deltaDistX;
			rc->mapX += rc->stepX;
			rc->side = 0;
			if (worldMap[rc->mapX][rc->mapY] > 0)
			{
				rc->hit = 1;
				if (rc->mapX > data->posX)
					rc->texNum = 4;
				else
					rc->texNum = 7;	
			}
		}
		else
		{
			rc->sideDistY += rc->deltaDistY;
			rc->mapY += rc->stepY;
			rc->side = 1;
			if (worldMap[rc->mapX][rc->mapY] > 0)
			{
				rc->hit = 1;
				if (rc->mapY > data->posY)
					rc->texNum = 2;
				else
					rc->texNum = 3;	
			}
		}
	}
	if (rc->side == 0)
		rc->perpWallDist = (rc->sideDistX - rc->deltaDistX);
	else
		rc->perpWallDist = (rc->sideDistY - rc->deltaDistY);
}

void	calc_texturing(t_data *data, t_rc *rc)
{
	rc->lineHeight = ((int)(SCREEN_HEIGHT / rc->perpWallDist)) * 2;
	rc->drawStart = -rc->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (rc->drawStart < 0)
		rc->drawStart = 0;
	rc->drawEnd = rc->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (rc->drawEnd >= SCREEN_HEIGHT)
		rc->drawEnd = SCREEN_HEIGHT - 1;
//	rc->texNum = worldMap[rc->mapX][rc->mapY] - 1;
	if (rc->side == 0)
		rc->wallX = data->posY + rc->perpWallDist * rc->rayDirY;
	else
		rc->wallX = data->posX + rc->perpWallDist * rc->rayDirX;
	rc->wallX -= floor((rc->wallX));
	rc->texX = (int)(rc->wallX * (double)(TEX_WIDTH));
	if (rc->side == 0 && rc->rayDirX > 0)
		rc->texX = TEX_WIDTH - rc->texX - 1;
	if (rc->side == 1 && rc->rayDirY < 0)
		rc->texX = TEX_WIDTH - rc->texX - 1;
	rc->step = 1.0 * TEX_HEIGHT / rc->lineHeight;
	rc->texPos = (rc->drawStart - SCREEN_HEIGHT / 2 \
		+ rc->lineHeight / 2) * rc->step;
	rc->y = rc->drawStart - 1;
}

void	draw_texture(t_data *data, t_rc *rc)
{
	while (++rc->y < rc->drawEnd)
	{
		rc->texY = (int)rc->texPos & (TEX_HEIGHT - 1);
		rc->texPos += rc->step;
		rc->color = data->texture[rc->texNum][TEX_HEIGHT * rc->texY + rc->texX];
		if (rc->side == 1)
			rc->color /= 2;
		my_mlx_pixel_put(data, rc->x, rc->y, rc->color);
	}
}

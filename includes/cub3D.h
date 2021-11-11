/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:08:57 by julian            #+#    #+#             */
/*   Updated: 2021/11/11 18:42:17 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <errno.h>
# include <time.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
#include <sys/time.h>

# define screenWidth	720
# define screenHeight	360
# define texWidth		64
# define texHeight		64
# define mapWidth		24
# define mapHeight		24


# define KEY_ANSI_A		(0X00)
# define KEY_ANSI_S		(0X01)
# define KEY_ANSI_D		(0X02)
# define KEY_ANSI_W		(0X0D)
# define KEY_LEFTARROW	(0X7B)
# define KEY_RIGHTARROW	(0X7C)
# define KEY_ESCAPE		(0X35)

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	int		mlx_img_width;
	int		mlx_img_height;
	char	*mlx_data_addr;
	char	*relative_path;
	int		mlx_bits_per_pixel;
	int		mlx_size_line;
	int		mlx_endian;

	double	posX;
	double	posY;

	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;

	unsigned int	buffer[screenHeight][screenWidth];
	int				texture[8][texWidth * texHeight + texWidth];

	double	time;
	double	oldTime;
	double	frameTime;

}			t_data;

#endif
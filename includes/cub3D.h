/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:08:57 by julian            #+#    #+#             */
/*   Updated: 2021/11/09 09:50:08 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <errno.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define screenWidth	640
# define screenHeight	480
# define texWidth		64
# define texHeight		64
# define mapWidth		24
# define mapHeight		24

# define IMG_EAGLE			"./images/eagle.pgn"
# define IMG_REDBRICK		"./images/redbrick.pgn"
# define IMG_PURPLESTONE	"./images/purplestone.pgn"
# define IMG_GREYSTONE		"./images/greystone.pgn"
# define IMG_BLUESTONE		"./images/bluestone.pgn"
# define IMG_MOSSY			"./images/mossy.pgn"
# define IMG_WOOD			"./images/wood.pgn"
# define IMG_COLORSTONE		"./images/colorstone.pgn"


# define KEY_ANSI_A		(0X00)
# define KEY_ANSI_S		(0X01)
# define KEY_ANSI_D		(0X02)
# define KEY_ANSI_W		(0X0D)
# define KEY_LEFTARROW	(0X7B)
# define KEY_RIGHTARROW	(0X7C)
# define KEY_ESCAPE		(0X35)

/* Struct 'img' for handling the game's tiles and sprites sizes */
typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}				t_img;

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

	t_img	*img[8];

}			t_data;



#endif
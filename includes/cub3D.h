/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:08:57 by julian            #+#    #+#             */
/*   Updated: 2021/11/08 10:21:06 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <errno.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define screenWidth	1280
# define screenHeight	720
# define mapWidth		24
# define mapHeight		24

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

	int		blue;
}			t_data;

#endif
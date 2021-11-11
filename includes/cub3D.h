/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:08:57 by julian            #+#    #+#             */
/*   Updated: 2021/11/11 13:52:10 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <errno.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define ESC_KEY 53
# define PLUS_KEY 69
# define MINUS_KEY 78
# define SPACE_KEY 49
# define ARROW_UP_KEY 126
# define ARROW_DOWN_KEY 125
# define ARROW_RIGHT_KEY 124
# define ARROW_LEFT_KEY 123
# define SCROLL_UP 4
# define SCROLL_DOWN 5

# define WIDTH	1280
# define HEIGHT	720

typedef struct s_img
{
	void	*ptr;
	char	*path;
	char	*addr;
	int		width;
	int		height;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
}			t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
}			t_data;

#endif
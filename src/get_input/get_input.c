/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:45:22 by jludt             #+#    #+#             */
/*   Updated: 2021/11/19 18:47:19 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	test_general(int argc, char *argv[])
{
	int	in;

	if (argc != 2)
	{
		printf("Error\n");
		printf("Program needs scene description file with .cub extension\n");
		printf(YELLOW"Usage: "RESET);
		return (printf("./cub3D .cub_file\n"));
	}
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4))
	{
		printf("Error\n");
		printf("Scene description file must have .cub extension\n");
		printf(YELLOW"Usage: "RESET);
		return (printf("./cub3D .cub_file\n"));
	}
	in = open(argv[1], O_RDONLY);
	if (in < 0)
	{
		printf("Error\n");
		return (printf("%s: %s\n", strerror(errno), argv[1]));
	}
	close(in);
	return (SUCCESS);
}

int	get_input(t_data *data, int argc, char *argv[])
{
	if (test_general(argc, argv))
		return (FAILURE);
	if (get_map_look(data, argv[1]))
		return (FAILURE);
	return (SUCCESS);
}

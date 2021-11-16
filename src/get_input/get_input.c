/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:45:22 by jludt             #+#    #+#             */
/*   Updated: 2021/11/15 18:56:50 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	test_general(int argc, char *argv[])
{
	int	in;

	if (argc != 2)
	{
		printf(RED"Error\n"RESET);
		printf("Program needs scene description file with .cub extension\n");
		printf(YELLOW"Usage: "RESET);
		return(printf("./cub3D .cub_file\n"));
	}
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 5))
	{
		printf("%s\n", argv[1] + (ft_strlen(argv[1]) - 4));
		printf(RED"Error\n"RESET);
		printf("Scene description file must have .cub extension\n");
				printf(YELLOW"Usage: "RESET);
		return(printf("./cub3D .cub_file\n"));
	}
	in = open(argv[1], O_RDONLY);
	if (in < 0)
	{
		printf(RED"Error\n"RESET);
		return(printf("%s: %s\n", strerror(errno), argv[1]));
	}
	close(in);
	return (SUCCESS);
}

int	get_map_look(t_data *data, char *file)
{
	int		in;
	char	*str;

	(void) *data;
	
	in = open(file, O_RDONLY);
	str = get_next_line(in);
	if (!str)
	{
		printf(RED"Error\n"RESET);
		return (printf("Empty .cub-file\n"));
	}
	while (str)
	{
		if (strncmp(str, "NO ", 3) && strncmp(str, "SO ", 3) 
			&& strncmp(str, "WE ", 3) && strncmp(str, "EA ", 3)
			&& strncmp(str, "F ", 2) && strncmp(str, "C ", 2))
		{
			free(str);
			printf(RED"Error\n"RESET);
			return (printf("Invalid identifier for texture or color\n"));
		}
		free(str);
		str = NULL;
		str = get_next_line(in);
	}
	
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 00:43:37 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/07 22:23:43 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_walk_through(t_graph *graph, int row, int col)
{
	if (graph->cats != graph->awake)
	{
		ft_printf("You have to wake up all Kiwis!\n");
		ft_change_position(graph, row, col);
	}
	else
	{
		ft_printf("Great Job! You Won :)\n");
		ft_free_destroy(graph);
	}
}

void	ft_put_image(t_graph *graph, void *img, int row, int col)
{
	mlx_put_image_to_window(graph->mlx, graph->win, \
			img, IMG_SIZE * col, IMG_SIZE * row);
}

void	ft_load_map(t_graph *graph)
{
	int	row;
	int	col;

	row = -1;
	while (++row < graph->row)
	{
		col = -1;
		while (++col < graph->col)
		{
			if (graph->map[row][col] == '1')
				ft_put_image(graph, graph->wall, row, col);
			else if (graph->map[row][col] == '0')
				ft_put_image(graph, graph->space, row, col);
			else if (graph->map[row][col] == 'C')
				ft_put_image(graph, graph->cat_img[0], row, col);
			else if (graph->map[row][col] == 'P')
				ft_put_image(graph, graph->ply_img, row, col);
			else if (graph->map[row][col] == 'E')
				ft_put_image(graph, graph->door[0], row, col);
		}
	}
}

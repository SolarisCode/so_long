/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 00:46:04 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/14 18:16:10 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf_bonus.h"
#include "so_long.h"

int	ft_free_destroy(t_graph *graph)
{
	mlx_destroy_image(graph->mlx, graph->wall);
	mlx_destroy_image(graph->mlx, graph->space);
	mlx_destroy_image(graph->mlx, graph->cat_img[0]);
	mlx_destroy_image(graph->mlx, graph->cat_img[1]);
	mlx_destroy_image(graph->mlx, graph->door[0]);
	mlx_destroy_image(graph->mlx, graph->door[1]);
	mlx_destroy_image(graph->mlx, graph->ply_img);
	mlx_destroy_window(graph->mlx, graph->win);
	ft_free_graph(graph);
	exit(0);
}

void	ft_change_position(t_graph *graph, int row, int col)
{
	if (graph->last_pos == '0')
		ft_put_image(graph, graph->space, graph->player[0], graph->player[1]);
	else if (graph->last_pos == 'W')
		ft_put_image(graph, graph->cat_img[1], graph->player[0], \
				graph->player[1]);
	else if (graph->last_pos == 'E')
		ft_put_image(graph, graph->door[0], graph->player[0], graph->player[1]);
	graph->map[graph->player[0]][graph->player[1]] = graph->last_pos;
	ft_put_image(graph, graph->ply_img, row, col);
	graph->last_pos = graph->map[row][col];
	graph->map[row][col] = 'P';
	graph->player[0] = row;
	graph->player[1] = col;
	graph->steps ++;
	ft_printf("Steps: %d\tKiwis: %d/%d\n", graph->steps, graph->cats, \
			graph->awake);
}

void	ft_check_door(t_graph *graph)
{
	int	row;
	int	col;

	row = -1;
	if (graph->cats == graph->awake)
	{
		while (++row < graph->row)
		{
			col = -1;
			while (++col < graph->col)
				if (graph->map[row][col] == 'E')
					ft_put_image(graph, graph->door[1], row, col);
		}
	}
	else
		return ;
}

void	ft_move_ply(t_graph *graph, int row, int col)
{
	if (graph->map[row][col] == '1')
		return ;
	else if (graph->map[row][col] == '0' || graph->map[row][col] == 'C' \
			|| graph->map[row][col] == 'W')
	{
		if (graph->map[row][col] == 'C')
		{
			graph->map[row][col] = 'W';
			graph->awake ++;
			ft_check_door(graph);
		}
		ft_change_position(graph, row, col);
	}
	else if (graph->map[row][col] == 'E')
		ft_walk_through(graph, row, col);
}

int	ft_key_hook(int keycode, t_graph *graph)
{
	if (keycode == ESC_KEY)
		ft_free_destroy(graph);
	else if (keycode == D_KEY)
		ft_move_ply(graph, graph->player[0], graph->player[1] + 1);
	else if (keycode == A_KEY)
		ft_move_ply(graph, graph->player[0], graph->player[1] - 1);
	else if (keycode == W_KEY)
		ft_move_ply(graph, graph->player[0] - 1, graph->player[1]);
	else if (keycode == S_KEY)
		ft_move_ply(graph, graph->player[0] + 1, graph->player[1]);
	return (0);
}

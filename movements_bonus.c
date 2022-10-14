/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:06:32 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/07 22:09:12 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_player_die(t_graph *graph)
{
	ft_printf("Oh no, You got Killed :(\n");
	ft_free_destroy(graph);
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
	ft_put_image(graph, graph->ply_img[0], row, col);
	graph->last_pos = graph->map[row][col];
	graph->map[row][col] = 'P';
	graph->player[0] = row;
	graph->player[1] = col;
	graph->steps ++;
	ft_put_string(graph);
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
	else if (graph->map[row][col] == 'G')
		ft_player_die(graph);
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

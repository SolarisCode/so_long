/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:10:08 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/07 22:23:56 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

int	ft_render(t_graph *graph)
{
	static int	p_num;
	static int	g_num;
	int			row;
	int			col;

	row = -1;
	usleep(100000);
	while (graph->map[++row])
	{
		col = -1;
		while (graph->map[row][++col])
		{
			if (graph->map[row][col] == 'P')
				ft_put_image(graph, graph->ply_img[p_num], row, col);
			else if (graph->map[row][col] == 'G')
				ft_put_image(graph, graph->gol_img[g_num], row, col);
		}
	}
	if (++p_num == 18)
		p_num = 0;
	if (++g_num == 12)
		g_num = 0;
	return (0);
}

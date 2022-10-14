/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:03:33 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/14 18:16:00 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_free_destroy(t_graph *graph)
{
	int	count;

	count = -1;
	mlx_destroy_image(graph->mlx, graph->wall);
	mlx_destroy_image(graph->mlx, graph->space);
	mlx_destroy_image(graph->mlx, graph->cat_img[0]);
	mlx_destroy_image(graph->mlx, graph->cat_img[1]);
	mlx_destroy_image(graph->mlx, graph->door[0]);
	mlx_destroy_image(graph->mlx, graph->door[1]);
	while (++count < 18)
		mlx_destroy_image(graph->mlx, graph->ply_img[count]);
	count = -1;
	while (++count < 12)
		mlx_destroy_image(graph->mlx, graph->gol_img[count]);
	mlx_destroy_window(graph->mlx, graph->win);
	ft_free_graph(graph);
	exit(0);
}

void	ft_put_string(t_graph *graph)
{
	char	*num;
	char	*steps;
	char	*kiwis;
	char	*tmp;

	num = ft_itoa(graph->steps);
	steps = ft_strjoin("Steps: ", num);
	free(num);
	num = ft_itoa(graph->cats);
	tmp = ft_strjoin("Kiwis: ", num);
	tmp = ft_strjoin_free(tmp, "/");
	free(num);
	num = ft_itoa(graph->awake);
	kiwis = ft_strjoin(tmp, num);
	ft_put_image(graph, graph->wall, 0, 0);
	mlx_string_put(graph->mlx, graph->win, 20, 20, 0xFFFFFF, steps);
	mlx_string_put(graph->mlx, graph->win, 20, 40, 0xFFFFFF, kiwis);
	free(num);
	free(steps);
	free(tmp);
	free(kiwis);
}

void	ft_load_golem(t_graph *graph)
{
	graph->gol_img[0] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_golem/golem1.xpm", &graph->img_wh, &graph->img_wh);
	graph->gol_img[1] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_golem/golem2.xpm", &graph->img_wh, &graph->img_wh);
	graph->gol_img[2] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_golem/golem3.xpm", &graph->img_wh, &graph->img_wh);
	graph->gol_img[3] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_golem/golem4.xpm", &graph->img_wh, &graph->img_wh);
	graph->gol_img[4] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_golem/golem5.xpm", &graph->img_wh, &graph->img_wh);
	graph->gol_img[5] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_golem/golem6.xpm", &graph->img_wh, &graph->img_wh);
	graph->gol_img[6] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_golem/golem7.xpm", &graph->img_wh, &graph->img_wh);
	graph->gol_img[7] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_golem/golem8.xpm", &graph->img_wh, &graph->img_wh);
	graph->gol_img[8] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_golem/golem9.xpm", &graph->img_wh, &graph->img_wh);
	graph->gol_img[9] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_golem/golem10.xpm", &graph->img_wh, &graph->img_wh);
	graph->gol_img[10] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_golem/golem11.xpm", &graph->img_wh, &graph->img_wh);
	graph->gol_img[11] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_golem/golem12.xpm", &graph->img_wh, &graph->img_wh);
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
				ft_put_image(graph, graph->ply_img[0], row, col);
			else if (graph->map[row][col] == 'E')
				ft_put_image(graph, graph->door[0], row, col);
			else if (graph->map[row][col] == 'G')
				ft_put_image(graph, graph->gol_img[0], row, col);
		}
	}
}

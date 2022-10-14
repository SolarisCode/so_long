/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulid_graphics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 00:33:01 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/07 19:56:18 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_load_wall_door(t_graph *graph)
{
	graph->wall = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/new_wall.xpm", &graph->img_wh, &graph->img_wh);
	graph->space = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/filling.xpm", &graph->img_wh, &graph->img_wh);
	graph->door[0] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_door/door1.xpm", &graph->img_wh, &graph->img_wh);
	graph->door[1] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_door/door2.xpm", &graph->img_wh, &graph->img_wh);
}

void	ft_load_ply_cat(t_graph *graph)
{
	graph->cat_img[0] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_cat/cat1.xpm", &graph->img_wh, &graph->img_wh);
	graph->cat_img[1] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_cat/cat.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch1.xpm", &graph->img_wh, &graph->img_wh);
}

void	ft_load_imgs(t_graph *graph)
{
	ft_load_ply_cat(graph);
	ft_load_wall_door(graph);
	ft_load_map(graph);
}

void	ft_start_graphics(t_graph *graph)
{
	graph->mlx = mlx_init();
	graph->win = mlx_new_window(graph->mlx, IMG_SIZE * graph->col, \
			IMG_SIZE * graph->row, "Wake Up Kiwi");
	graph->last_pos = '0';
	ft_load_imgs(graph);
	ft_printf("Steps: %d\tKiwis: %d/%d\n", graph->steps, graph->cats, \
			graph->awake);
	mlx_key_hook(graph->win, ft_key_hook, graph);
	mlx_hook(graph->win, 17, 0, ft_free_destroy, graph);
	mlx_loop(graph->mlx);
}

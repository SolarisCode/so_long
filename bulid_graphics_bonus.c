/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulid_graphics_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:59:34 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/07 17:01:28 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_load_player(t_graph *graph)
{
	graph->ply_img[0] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch1.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[1] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch2.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[2] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch3.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[3] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch4.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[4] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch5.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[5] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch6.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[6] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch7.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[7] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch8.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[8] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch9.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[9] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch10.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[10] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch11.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[11] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch12.xpm", &graph->img_wh, &graph->img_wh);
}

void	ft_load_ply_cat(t_graph *graph)
{
	graph->cat_img[0] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_cat/cat1.xpm", &graph->img_wh, &graph->img_wh);
	graph->cat_img[1] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_cat/cat.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[12] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch13.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[13] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch14.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[14] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch15.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[15] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch16.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[16] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch17.xpm", &graph->img_wh, &graph->img_wh);
	graph->ply_img[17] = mlx_xpm_file_to_image(graph->mlx, \
			"./art_work/xpm_right/witch18.xpm", &graph->img_wh, &graph->img_wh);
}

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

void	ft_load_imgs(t_graph *graph)
{
	ft_load_player(graph);
	ft_load_ply_cat(graph);
	ft_load_wall_door(graph);
	ft_load_golem(graph);
	ft_load_map(graph);
}

void	ft_start_graphics(t_graph *graph)
{
	graph->mlx = mlx_init();
	graph->win = mlx_new_window(graph->mlx, IMG_SIZE * graph->col, \
			IMG_SIZE * graph->row, "Wake Up Kiwi");
	graph->last_pos = '0';
	ft_load_imgs(graph);
	ft_put_string(graph);
	mlx_key_hook(graph->win, ft_key_hook, graph);
	mlx_hook(graph->win, 17, 0, ft_free_destroy, graph);
	mlx_loop_hook(graph->mlx, ft_render, graph);
	mlx_loop(graph->mlx);
}

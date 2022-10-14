/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:51:37 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/14 12:00:01 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
# include <sys/fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include "./ft_printf/ft_printf_bonus.h"
# include "./ft_printf/libft/libft.h"
# include "minilibx-linux/mlx.h"

# if defined (__linux__)
#  define IMG_SIZE 100
#  define ESC_KEY 65307
#  define W_KEY 119
#  define S_KEY 115
#  define D_KEY 100
#  define A_KEY 97
# elif defined (__APPLE__)
#  define IMG_SIZE 100
#  define ESC_KEY 53
#  define W_KEY 13
#  define S_KEY 1
#  define D_KEY 2
#  define A_KEY 0
# endif

typedef struct s_graph
{
	char	**map;
	void	*mlx;
	void	*win;
	void	*wall;
	void	*space;
	void	*ply_img;
	char	last_pos;
	void	*cat_img[2];
	void	*door[2];
	int		player[2];
	int		img_wh;
	int		steps;
	int		row;
	int		col;
	int		cats;
	int		gate;
	int		awake;
}			t_graph;

t_graph	*ft_check_map(char *file);
void	ft_start_graphics(t_graph *graph);
int		ft_key_hook(int keycode, t_graph *graph);
int		ft_render(t_graph *graph);
void	ft_move_ply(t_graph *graph, int row, int col);
void	ft_player_die(t_graph *graph);
void	ft_check_door(t_graph *graph);
void	ft_change_position(t_graph *graph, int row, int col);
int		ft_free_destroy(t_graph *graph);
void	ft_load_imgs(t_graph *graph);
void	ft_load_map(t_graph *graph);
void	ft_put_image(t_graph *graph, void *img, int row, int col);
void	ft_load_wall_door(t_graph *graph);
void	ft_load_ply_cat(t_graph *graph);
void	ft_load_player(t_graph *graph);
bool	ft_ispath(t_graph *graph);
void	ft_mark_path(t_graph *graph, int row, int col, int **visited);
bool	ft_find_path(t_graph *graph, int **visited);
bool	ft_maplen(char *file, t_graph *graph);
bool	ft_get_map(char *file, t_graph *graph);
bool	ft_validate_map(t_graph *graph);
int		ft_check_p_c_e(t_graph *graph);
void	ft_free_graph(t_graph *graph);
void	ft_walk_through(t_graph *graph, int row, int col);

#endif

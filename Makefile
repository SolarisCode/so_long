# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 14:28:14 by melkholy          #+#    #+#              #
#    Updated: 2022/10/14 10:46:54 by melkholy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = so_long
CDIR = .
PRINTFDIR = ./ft_printf/
MLXDIR = ./mlx/
MLX_L_DIR = ./minilibx-linux/
LIBFTPRINTF = ./ft_printf/libftprintf.a
LIBMLX = ./mlx/libmlx.a
MLX_LINUX = ./minilibx-linux/libmlx_Linux.a
CFLAGS = -Wall -Werror -Wextra

CFILES = main.c bulid_graphics.c check_path.c \
		 launch_map.c movements.c

BFILES = main_bonus.c bulid_graphics_bonus.c check_path_bonus.c \
		 launch_map_bonus.c movements_bonus.c sprite_bonus.c

LCFILES = main.c bulid_graphics.c check_path.c \
		 launch_map.c linux_movements.c

LBFILES = main_bonus.c bulid_graphics_bonus.c check_path_bonus.c \
		 linux_launch_map_bonus.c movements_bonus.c sprite_bonus.c

OBJ = ${CFILES:.c=.o}
BOBJ = ${BFILES:.c=.o}
LOBJ = ${LCFILES:.c=.o}
LBOBJ = ${LBFILES:.c=.o}

all : $(NAME)

$(NAME) : $(LIBFTPRINTF) $(LIBMLX)
	@$(CC) $(CFLAGS) -c $(CFILES)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFTPRINTF) $(LIBMLX) -framework OpenGL \
		-framework AppKit -o $(NAME)

linux : $(LIBFTPRINTF) $(MLX_LINUX)
	@$(CC) $(CFLAGS) -c $(LCFILES) -I$(PRINTFDIR) -L$(PRINTFDIR) -lftprintf \
		-I$(MLX_L_DIR) -L$(MLX_L_DIR) -lmlx_linux
	@$(CC) $(CFLAGS) $(LOBJ) -L$(PRINTFDIR) -lftprintf \
		$(MLX_LINUX) -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

bonus : $(LIBFTPRINTF) $(LIBMLX)
	@$(CC) $(CFLAGS) -c $(BFILES)
	@$(CC) $(CFLAGS) $(BOBJ) $(LIBFTPRINTF) $(LIBMLX) -framework OpenGL \
		-framework AppKit -o $(NAME)

lbonus : $(LIBFTPRINTF) $(MLX_LINUX)
	@$(CC) $(CFLAGS) -c $(LBFILES) -I$(PRINTFDIR) -L$(PRINTFDIR) -lftprintf \
		-I$(MLX_L_DIR) -L$(MLX_L_DIR) -lmlx_linux
	@$(CC) $(CFLAGS) $(LBOBJ) -L$(PRINTFDIR) -lftprintf \
		$(MLX_LINUX) -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFTPRINTF) :
	@make -C $(PRINTFDIR)

$(LIBMLX) :
	@make -C $(MLXDIR)

$(MLX_LINUX) :
	@make -C $(MLX_L_DIR)

lclean :
	@make clean -C $(PRINTFDIR)
	@make clean -C $(MLX_L_DIR)
	@rm -f $(LOBJ)
	@rm -f $(LBOBJ)

clean :
	@make clean -C $(PRINTFDIR)
	@make clean -C $(MLXDIR)
	@rm -f $(OBJ)
	@rm -f $(BOBJ)

fclean : clean lclean
	@make fclean -C $(PRINTFDIR)
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re linux lclean bonus lbonus

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:28:39 by anollero          #+#    #+#             */
/*   Updated: 2023/11/13 12:10:14 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <mlx.h>
# include "get_next_line.h"
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_so_long_info
{
	char	**map;
	int		nitems;
	int		posx;
	int		posy;
	void	*mlx;
	int		moves;
	int		w_len_y;
	int		w_len_x;
	void	*player_img;
	void	*wall_img;
	void	*floor_img;
	void	*exit_img;
	void	*colectible_img;
	void	*exit_player_img;
	void	*window;
	int		in_exit;
	int		colect_check;
	int		exit_check;
}	t_so_long_info;

int		close_everything(void);
int		check_valid(char **map, int *nitems);
int		check_car(char **map, t_so_long_info *info);
int		ft_strlen_map(char *str);
int		check_rectangle(char **map);
int		check_walls(char **map);
void	images_init(t_so_long_info *info);
void	draw_cell(int row, int column, t_so_long_info *info);
int		draw_map(t_so_long_info *info);
void	move(int dirx, int diry, t_so_long_info *info);
int		key_pressed(int keycode, t_so_long_info *info);
void	free_map(char **map);
int		check_winnable_aux(char **map, int posx, int posy,
			t_so_long_info *info);
int		check_winnable(char **map, int posx, int posy,
			t_so_long_info *info);
int		check_winnable_prep(char **map, int posx, int posy,
			t_so_long_info *info);
void	check_success(t_so_long_info *info, int dirx, int diry);

#endif
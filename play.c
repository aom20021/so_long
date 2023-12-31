/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:06:56 by anollero          #+#    #+#             */
/*   Updated: 2023/11/15 10:28:35 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	images_init(t_so_long_info *info)
{
	int	img_size;

	img_size = 64;
	info->player_img = mlx_xpm_file_to_image(info->mlx,
			"resources/sprites/Player.xpm", &img_size, &img_size);
	info->colectible_img = mlx_xpm_file_to_image(info->mlx,
			"resources/sprites/Colectible.xpm", &img_size, &img_size);
	info->exit_img = mlx_xpm_file_to_image(info->mlx,
			"resources/sprites/Exit.xpm", &img_size, &img_size);
	info->wall_img = mlx_xpm_file_to_image(info->mlx,
			"resources/sprites/Wall.xpm", &img_size, &img_size);
	info->floor_img = mlx_xpm_file_to_image(info->mlx,
			"resources/sprites/Floor.xpm", &img_size, &img_size);
	info->exit_player_img = mlx_xpm_file_to_image(info->mlx,
			"resources/sprites/Exit_player.xpm", &img_size, &img_size);
}

void	draw_cell(int row, int column, t_so_long_info *info)
{
	if (info->map[row][column] == '1')
		mlx_put_image_to_window(info->mlx,
			info->window, info->wall_img, 64 * column, 64 * row);
	if (info->map[row][column] == '0')
		mlx_put_image_to_window(info->mlx,
			info->window, info->floor_img, 64 * column, 64 * row);
	if (info->map[row][column] == 'P')
		mlx_put_image_to_window(info->mlx,
			info->window, info->player_img, 64 * column, 64 * row);
	if (info->map[row][column] == 'C')
		mlx_put_image_to_window(info->mlx,
			info->window, info->colectible_img, 64 * column, 64 * row);
	if (info->map[row][column] == 'E')
		mlx_put_image_to_window(info->mlx,
			info->window, info->exit_img, 64 * column, 64 * row);
	if (info->map[row][column] == 'K')
		mlx_put_image_to_window(info->mlx,
			info->window, info->exit_player_img, 64 * column, 64 * row);
}

int	draw_map(t_so_long_info *info)
{
	int	column;
	int	row;

	column = 0;
	row = 0;
	while (row < info->w_len_y)
	{
		while (column < info->w_len_x)
		{
			draw_cell(row, column, info);
			column++;
		}
		column = 0;
		row++;
	}
	return (0);
}

void	check_success(t_so_long_info *info, int dirx, int diry)
{
	if (info->map[info->posx + dirx][info->posy + diry] == 'E'
			&& info->nitems == 0)
	{
		ft_putstr_fd("FELICIDADES\n", 1);
		close_everything();
	}
}

void	move(int dirx, int diry, t_so_long_info *info)
{
	if (info->map[info->posx + dirx][info->posy + diry] != '1')
	{
		if (info->map[info->posx + dirx][info->posy + diry] == 'C')
			info->nitems--;
		ft_putnbr_fd(++info->moves, 0);
		ft_putchar_fd('\n', 1);
		info->map[info->posx][info->posy] = '0';
		if (info->in_exit == 1)
		{
			info->in_exit = 0;
			info->map[info->posx][info->posy] = 'E';
		}
		check_success(info, dirx, diry);
		info->posx = info->posx + dirx;
		info->posy = info->posy + diry;
		if (info->map[info->posx][info->posy] == 'E')
		{
			info->map[info->posx][info->posy] = 'K';
			info->in_exit = 1;
		}
		else
			info->map[info->posx][info->posy] = 'P';
	}
}

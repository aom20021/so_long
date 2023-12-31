/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 14:45:24 by anollero          #+#    #+#             */
/*   Updated: 2023/11/15 13:38:54 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include <stdio.h>

int	close_everything(void)
{
	exit(0);
}

int	key_pressed(int keycode, t_so_long_info *info)
{
	if (keycode == 13)
		move(-1, 0, info);
	if (keycode == 0)
		move(0, -1, info);
	if (keycode == 1)
		move(1, 0, info);
	if (keycode == 2)
		move(0, 1, info);
	if (keycode == 53)
		close_everything();
	return (0);
}

char	**open_map(char *filename)
{
	int		fd_map;
	int		nlines;
	char	**ret;
	int		count;

	nlines = 0;
	count = 0;
	fd_map = open(filename, O_RDONLY);
	if (fd_map == -1)
		return (NULL);
	nlines = count_lines(fd_map);
	fd_map = open(filename, O_RDONLY);
	ret = (char **)ft_calloc(nlines + 1, sizeof(char *));
	while (count <= nlines)
		ret[count++] = get_next_line(fd_map);
	close(fd_map);
	return (ret);
}

int	init_map(char *filename, t_so_long_info *info)
{
	if (!ft_strncmp(filename + (ft_strlen(filename) - 4), ".ber", 4))
	{
		info->map = open_map(filename);
		if (info->map != NULL && (ft_strlen_map(info->map[0]) > 40
				|| count_lines(open(filename, O_RDONLY)) > 22))
		{
			ft_putstr_fd("El mapa es muy grande\n", 2);
			exit(0);
		}
	}
	else
		return (0);
	if (info->map != NULL && check_car(info->map, info)
		&& check_valid(info->map, &info->nitems)
		&& check_rectangle(info->map) && check_walls(info->map)
		&& check_winnable_prep(info->map, info->posy, info->posx, info))
		return (1);
	else
		return (0);
}

int	main(int argc, char *argv[])
{
	t_so_long_info	*info;

	info = ft_calloc(1, sizeof(t_so_long_info));
	if (init_map(argv[argc - 1], info))
	{
		info->mlx = mlx_init();
		images_init(info);
		info->window = mlx_new_window(info->mlx, info->w_len_x * 64,
				info->w_len_y * 64, "so_long");
		mlx_loop_hook(info->mlx, draw_map, info);
		mlx_key_hook(info->window, key_pressed, info);
		mlx_hook(info->window, 17, 0, close_everything, NULL);
		mlx_loop(info->mlx);
	}
	else
		ft_putstr_fd("Error\n", 0);
	close_everything();
}

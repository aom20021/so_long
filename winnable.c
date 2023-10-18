/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winnable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:06:05 by anollero          #+#    #+#             */
/*   Updated: 2023/10/18 17:11:23 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	free_map(char **map)
{
	int	count;

	count = 0;
	while (map[count] != NULL)
	{
		free(map[count]);
		count++;
	}
	free(map);
}

int	check_winnable_aux(char **map, int posx, int posy, t_so_long_info *info)
{
	if (posx < 0 || posy < 0 || map[posy][posx] == '1')
		return (0);
	if (map[posy][posx] == 'E')
		info->exit_check = 1;
	if (map[posy][posx] == 'E' && info->colect_check == 0)
		return (1);
	if (info->exit_check == 1 && info->colect_check == 0)
		return (1);
	if (map[posy][posx] == 'C')
		(info->colect_check)--;
	map[posy][posx] = '1';
	if (check_winnable_aux(map, posx - 1, posy, info)
		|| check_winnable_aux(map, posx + 1, posy, info)
		|| check_winnable_aux(map, posx, posy - 1, info)
		|| check_winnable_aux(map, posx, posy + 1, info))
		return (1);
	return (0);
}

int	check_winnable(char **map, int posx, int posy, t_so_long_info *info)
{
	if (posx < 0 || posy < 0 || map[posy][posx] == '1')
		return (0);
	if (map[posy][posx] == 'E')
		return (1);
	map[posy][posx] = '1';
	if ((check_winnable_aux(map, posx - 1, posy, info)
			|| check_winnable_aux(map, posx + 1, posy, info)
			|| check_winnable_aux(map, posx, posy - 1, info)
			|| check_winnable_aux(map, posx, posy + 1, info))
		&& info->colect_check == 0)
		return (1);
	if (info->exit_check == 1 && info->colect_check == 0)
		return (1);
	return (0);
}

int	check_winnable_prep(char **map, int posx, int posy, t_so_long_info *info)
{
	char	**auxmap;
	int		size;
	int		exit;

	size = 0;
	exit = 0;
	while (map[size] != NULL)
		size++;
	auxmap = ft_calloc(size, sizeof(char *));
	info->w_len_y = size;
	info->w_len_x = ft_strlen_map(map[0]);
	size = 0;
	while (map[size] != NULL)
	{
		auxmap[size] = ft_strdup(map[size]);
		size++;
	}
	info->colect_check = info->nitems;
	info->exit_check = 0;
	return (check_winnable(auxmap, posx, posy, info));
}

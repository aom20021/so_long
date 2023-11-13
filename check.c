/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:02:32 by anollero          #+#    #+#             */
/*   Updated: 2023/10/30 16:00:54 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

int	check_valid(char **map, int *nitems)
{
	int	posx;
	int	posy;
	int	player;
	int	exit;

	posy = 0;
	player = 0;
	exit = 0;
	while (map[posy] != NULL)
	{
		posx = 0;
		while (map[posy][posx] != '\0')
		{
			if (map[posy][posx] == 'P')
				player++;
			if (map[posy][posx] == 'E')
				exit++;
			if (map[posy][posx++] == 'C')
				(*nitems)++;
		}
		posy++;
	}
	if ((*nitems) == 0 || player > 1 || exit > 1)
		return (0);
	return (1);
}

int	check_car(char **map, t_so_long_info *info)
{
	int	posx;
	int	posy;

	posy = 0;
	while (map[posy] != NULL)
	{
		posx = 0;
		while (map[posy][posx] != '\0')
		{
			if (map[posy][posx] != 'P' && map[posy][posx] != 'E'
				&& map[posy][posx] != '1' && map[posy][posx] != '0'
				&& map[posy][posx] != '\n' && map[posy][posx] != 'C')
				return (0);
			if (map[posy][posx] == 'P')
			{
				info->posy = posx;
				info->posx = posy;
			}	
			posx++;
		}
		posy++;
	}
	return (1);
}

int	ft_strlen_map(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0' && str[count] != '\n')
		count++;
	return (count);
}

int	check_rectangle(char **map)
{
	int	count;
	int	len;

	count = 0;
	if (map[0] != NULL)
		len = ft_strlen_map(map[0]);
	while (map[count] != NULL)
	{
		if (ft_strlen_map(map[count]) != len)
			return (0);
		count++;
	}
	return (1);
}

int	check_walls(char **map)
{
	int	posx;
	int	posy;

	posy = 0;
	while (map[posy] != NULL)
	{
		posx = 0;
		while (map[posy][posx] != '\0')
		{
			if ((posy == 0 && posx < ft_strlen_map(map[posy]))
				|| map[posy + 1] == NULL
				|| posx == 0 || posx == ft_strlen_map(map[posy]) - 1)
			{
				if (map[posy][posx] != '1')
					return (0);
			}
			posx++;
		}
		posy++;
	}
	return (1);
}

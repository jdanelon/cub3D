/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:52:24 by jdanelon          #+#    #+#             */
/*   Updated: 2021/02/23 14:44:05 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	int	is_border(t_map *map, int x, int y)
{
	if (x == 0 || y == 0 || x == (map->width[y] - 1) || y == (map->height - 1))
		return (OK);
	return (ERROR);
}

int			flood_fill(t_window *win_infos, char **map, int x, int y)
{
	if (map[y][x] != '0' && map[y][x] != '1' &&
			map[y][x] != '2' && map[y][x] != '.')
		return (ERROR);
	if (map[y][x] == '0')
	{
		map[y][x] = '.';
		if (is_border(win_infos->map, x, y))
			return (ERROR);
		else
		{
			if (!flood_fill(win_infos, map, x, y - 1))
				return (ERROR);
			if (!flood_fill(win_infos, map, x, y + 1))
				return (ERROR);
			if (!flood_fill(win_infos, map, x - 1, y))
				return (ERROR);
			if (!flood_fill(win_infos, map, x + 1, y))
				return (ERROR);
		}
	}
	return (OK);
}

void		free_map_copy(t_window *win_infos, char **copy)
{
	int	i;

	i = 0;
	while (i < win_infos->map->height)
		free(copy[i++]);
	free(copy);
}

int			check_map_content(t_window *win_infos, char **map)
{
	int	i;
	int	j;

	j = 0;
	while (j < win_infos->map->height)
	{
		i = 0;
		while (i < win_infos->map->width[j])
		{
			if (map[j][i] != '0' && map[j][i] != '1' &&
					map[j][i] != '2' && map[j][i] != ' ')
				return (ERROR);
			i++;
		}
		j++;
	}
	return (OK);
}

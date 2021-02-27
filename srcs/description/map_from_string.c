/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_from_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:50:44 by jdanelon          #+#    #+#             */
/*   Updated: 2021/02/13 19:20:36 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	void	get_map_width(t_window *win_infos, char *str)
{
	int	i;
	int	j;
	int	len;
	int	*width;

	i = 0;
	j = 0;
	width = (int *)malloc(win_infos->map->height * sizeof(int));
	ft_bzero(width, win_infos->map->height * sizeof(int));
	win_infos->map->max_width = 0;
	while (i < win_infos->map->height)
	{
		len = 0;
		while (str[j] != '\n' && str[j])
		{
			j++;
			len++;
		}
		width[i++] = len;
		if (len > win_infos->map->max_width)
			win_infos->map->max_width = len;
		j++;
	}
	win_infos->map->width = width;
}

static	char	**malloc_map(t_window *win_infos)
{
	int		i;
	char	**map;

	i = 0;
	map = (char **)malloc((win_infos->map->height + 1) * sizeof(char *));
	ft_bzero(map, (win_infos->map->height + 1) * sizeof(char *));
	while (i < win_infos->map->height)
	{
		map[i] = (char *)malloc((win_infos->map->width[i] + 1) * sizeof(char));
		ft_bzero(map[i], (win_infos->map->width[i] + 1) * sizeof(char));
		i++;
	}
	win_infos->tile_size_x = win_infos->width /
		(double)win_infos->map->max_width;
	win_infos->tile_size_y = win_infos->height /
		(double)win_infos->map->height;
	return (map);
}

static	char	**init_map(t_window *win_infos, char **map, char *str)
{
	int	i;
	int	u;
	int	cursor;

	i = 0;
	u = 0;
	while (u < win_infos->map->height)
	{
		cursor = 0;
		while (str[i] && str[i] != '\n')
		{
			map[u][cursor++] = str[i];
			if ((str[i] == 'N' || str[i] == 'S' || str[i] == 'W' ||
					str[i] == 'E') && !win_infos->map->letter)
			{
				set_start_position(win_infos, cursor, str[i], u);
				win_infos->map->letter = 1;
				map[u][cursor - 1] = '0';
			}
			i++;
		}
		map[u++][cursor] = '\0';
		i++;
	}
	return (map);
}

static	int		check_map_norme(t_window *win_infos, char **map)
{
	int		i;
	int		x;
	int		y;
	char	**copy;

	if (!*map || !map)
		return (ERROR);
	i = 0;
	x = (int)floor(win_infos->player->x / win_infos->tile_size_x);
	y = (int)floor(win_infos->player->y / win_infos->tile_size_y);
	copy = (char **)malloc((win_infos->map->height + 1) * sizeof(char *));
	ft_bzero(copy, (win_infos->map->height + 1) * sizeof(char *));
	while (i < win_infos->map->height)
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	if (win_infos->player->x != -20.0 && win_infos->player->y != -20.0 &&
			!flood_fill(win_infos, copy, x, y))
	{
		free_map_copy(win_infos, copy);
		return (ERROR);
	}
	free_map_copy(win_infos, copy);
	return (OK);
}

char			**map_from_string(t_window *win_infos, char *str)
{
	int		i;
	char	**map;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			win_infos->map->height++;
		i++;
		if (!str[i] && i > 0 && str[i - 1] != '\n')
			win_infos->map->height++;
	}
	get_map_width(win_infos, str);
	map = malloc_map(win_infos);
	map = init_map(win_infos, map, str);
	free(str);
	if (!check_map_content(win_infos, map))
		leave(win_infos, "Error\nIn map norme", -2);
	if (!check_map_norme(win_infos, map))
		leave(win_infos, "Error\nIn map norme", -2);
	if (win_infos->player->x == -20.0 || win_infos->player->y == -20.0)
		leave(win_infos, "Error\nPlayer position/direction was not set", -2);
	return (map);
}

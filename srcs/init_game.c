/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:55:25 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/30 17:22:14 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_game_player(t_window *win_infos)
{
	win_infos->player = (t_player *)malloc(sizeof(t_player));
	ft_bzero(win_infos->player, sizeof(t_player));
	win_infos->player->x = -20.0;
	win_infos->player->y = -20.0;
	win_infos->player->turn_direction = 0;
	win_infos->player->walk_direction = 0;
	win_infos->player->rotation_angle = -20.0;
	win_infos->player->move_speed = 2.0;
	win_infos->player->rotation_speed = 2 * (PI / 180);
	return (OK);
}

int	init_game_sprite(t_window *win_infos)
{
	win_infos->sprite = (t_image *)malloc(sizeof(t_image));
	ft_bzero(win_infos->sprite, sizeof(t_image));
	win_infos->sprites_on_screen =
		(t_sprite_list *)malloc(sizeof(t_sprite_list));
	ft_bzero(win_infos->sprites_on_screen, sizeof(t_sprite_list));
	win_infos->sprites_on_screen->x = -20;
	win_infos->sprites_on_screen->y = -20;
	return (OK);
}

int	init_game_textures(t_window *win_infos, int nbr_textures)
{
	int	count;

	count = 0;
	win_infos->textures = (t_image **)malloc(sizeof(t_image *) * nbr_textures);
	ft_bzero(win_infos->textures, sizeof(t_image *) * nbr_textures);
	while (count < nbr_textures)
	{
		win_infos->textures[count] = (t_image *)malloc(sizeof(t_image));
		ft_bzero(win_infos->textures[count], sizeof(t_image));
		count++;
	}
	return (OK);
}

int	init_game_map(t_window *win_infos, const char *map_name)
{
	win_infos->map = (t_map *)malloc(sizeof(t_map));
	ft_bzero(win_infos->map, sizeof(t_map));
	if (ft_strnstr(map_name, ".cub", ft_strlen(map_name)))
		win_infos->map->map_name = map_name;
	else
		leave(win_infos, "Error\nFile is not '.cub'", -2);
	win_infos->map->width = 0;
	win_infos->map->height = 0;
	win_infos->map->letter = 0;
	return (OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:54:17 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/30 14:39:23 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	event_key_pressed(int key, void *param)
{
	int			i;
	t_window	*win_infos;

	i = 0;
	win_infos = (t_window *)param;
	if (key == ESC)
		leave(win_infos, "", 0);
	else if (key == FORWARD)
		win_infos->player->walk_direction = 1;
	else if (key == BACKWARD)
		win_infos->player->walk_direction = -1;
	else if (key == CAM_LEFT)
		win_infos->player->turn_direction = -1;
	else if (key == CAM_RIGHT)
		win_infos->player->turn_direction = 1;
	else if (key == LEFT)
		win_infos->player->move_sideways = 1;
	else if (key == RIGHT)
		win_infos->player->move_sideways = -1;
	return (OK);
}

int	event_key_released(int key, void *param)
{
	t_window	*win_infos;

	win_infos = (t_window *)param;
	if (key == FORWARD)
		win_infos->player->walk_direction = 0;
	else if (key == BACKWARD)
		win_infos->player->walk_direction = 0;
	else if (key == CAM_LEFT)
		win_infos->player->turn_direction = 0;
	else if (key == CAM_RIGHT)
		win_infos->player->turn_direction = 0;
	else if (key == LEFT)
		win_infos->player->move_sideways = 0;
	else if (key == RIGHT)
		win_infos->player->move_sideways = 0;
	return (OK);
}

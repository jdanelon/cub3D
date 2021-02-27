/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:53:43 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/26 11:32:15 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_start_position(t_window *win_infos, int cursor, char dir, int u)
{
	if (dir == 'N')
		win_infos->player->rotation_angle = -PI / 2;
	else if (dir == 'S')
		win_infos->player->rotation_angle = PI / 2;
	else if (dir == 'W')
		win_infos->player->rotation_angle = PI;
	else if (dir == 'E')
		win_infos->player->rotation_angle = 0.0;
	win_infos->player->x = ((cursor - 1) + 0.5) * win_infos->tile_size_x;
	win_infos->player->y = (u + 0.5) * win_infos->tile_size_y;
}

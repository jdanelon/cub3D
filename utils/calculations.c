/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:52:11 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/26 11:35:51 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	normalize_angle(double ray_angle)
{
	double	angle;

	angle = remainder(ray_angle, 2 * PI);
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
}

double	distance(t_window *win_infos, double x1, double y1)
{
	double	x2;
	double	y2;
	double	dist;

	x2 = pow((x1 - win_infos->player->x), 2);
	y2 = pow((y1 - win_infos->player->y), 2);
	dist = sqrt(x2 + y2);
	return (dist);
}

double	get_relative_distance(t_window *win_infos, t_draw_sprite *ds)
{
	double	dx;
	double	dy;
	double	theta;
	double	omega;
	double	displacement;

	dx = ds->sprite_x - win_infos->player->x;
	dy = ds->sprite_y - win_infos->player->y;
	theta = atan2(dy, dx);
	theta = normalize_angle(theta);
	omega = win_infos->player->rotation_angle - theta;
	omega = normalize_angle(omega);
	if (((omega - 2 * PI) > -win_infos->fov_angle / 2) &&
			((omega - 2 * PI) < win_infos->fov_angle / 2))
		omega -= 2 * PI;
	else if (((omega + 2 * PI) > -win_infos->fov_angle / 2) &&
			((omega + 2 * PI) < win_infos->fov_angle / 2))
		omega += 2 * PI;
	displacement = (omega * win_infos->width) / win_infos->fov_angle;
	ds->angle = theta;
	return (displacement);
}

int		sprite_on_fov(t_window *win_infos, t_draw_sprite *ds)
{
	if (ds->angle > (win_infos->player->rotation_angle -
			win_infos->fov_angle / 2) &&
			ds->angle < (win_infos->player->rotation_angle +
			win_infos->fov_angle / 2))
		return (OK);
	else if ((ds->angle - 2 * PI) >
			(win_infos->player->rotation_angle - win_infos->fov_angle / 2) &&
			(ds->angle - 2 * PI) <
			(win_infos->player->rotation_angle + win_infos->fov_angle / 2))
		return (OK);
	else if ((ds->angle + 2 * PI) >
			(win_infos->player->rotation_angle - win_infos->fov_angle / 2) &&
			(ds->angle + 2 * PI) <
			(win_infos->player->rotation_angle + win_infos->fov_angle / 2))
		return (OK);
	return (ERROR);
}

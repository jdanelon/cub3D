/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:54:00 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/26 11:32:24 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	void	horizontal_values(t_window *win_infos, t_ray *ray)
{
	ray->y_intercept_horizontal = floor(win_infos->player->y /
		win_infos->tile_size_y) * win_infos->tile_size_y;
	ray->y_intercept_horizontal += ray->facing_down ?
		win_infos->tile_size_y : 0;
	ray->x_intercept_horizontal = win_infos->player->x +
		(ray->y_intercept_horizontal - win_infos->player->y) /
		tan(ray->rotation_angle);
	ray->y_step_horizontal = win_infos->tile_size_y;
	ray->y_step_horizontal *= ray->facing_up ? -1 : 1;
	ray->x_step_horizontal = win_infos->tile_size_y / tan(ray->rotation_angle);
	ray->x_step_horizontal *= (ray->facing_left &&
		ray->x_step_horizontal > 0) ? -1 : 1;
	ray->x_step_horizontal *= (ray->facing_right &&
		ray->x_step_horizontal < 0) ? -1 : 1;
}

static	void	horizontal_intercept(t_window *win_infos, t_ray *ray)
{
	double	next_horizontal_touch_x;
	double	next_horizontal_touch_y;

	horizontal_values(win_infos, ray);
	next_horizontal_touch_x = ray->x_intercept_horizontal;
	next_horizontal_touch_y = ray->y_intercept_horizontal;
	while (next_horizontal_touch_x >= 0 && next_horizontal_touch_x <=
			win_infos->width && next_horizontal_touch_y >= 0 &&
			next_horizontal_touch_y <= win_infos->height)
	{
		if (has_wall_at(win_infos, next_horizontal_touch_x,
				next_horizontal_touch_y - (ray->facing_up ? 1 : 0) +
				(ray->facing_down ? 1 : 0)))
		{
			ray->horizontal_wall_hit = 1;
			ray->horizontal_distance = distance(win_infos,
				next_horizontal_touch_x, next_horizontal_touch_y);
			break ;
		}
		else
		{
			next_horizontal_touch_x += ray->x_step_horizontal;
			next_horizontal_touch_y += ray->y_step_horizontal;
		}
	}
}

static	void	vertical_values(t_window *win_infos, t_ray *ray)
{
	ray->x_intercept_vertical = floor(win_infos->player->x /
		win_infos->tile_size_x) * win_infos->tile_size_x;
	ray->x_intercept_vertical += ray->facing_right ? win_infos->tile_size_x : 0;
	ray->y_intercept_vertical = win_infos->player->y +
		(ray->x_intercept_vertical - win_infos->player->x) *
		tan(ray->rotation_angle);
	ray->x_step_vertical = win_infos->tile_size_x;
	ray->x_step_vertical *= ray->facing_left ? -1 : 1;
	ray->y_step_vertical = win_infos->tile_size_x * tan(ray->rotation_angle);
	ray->y_step_vertical *= (ray->facing_up &&
		ray->y_step_vertical > 0) ? -1 : 1;
	ray->y_step_vertical *= (ray->facing_down &&
		ray->y_step_vertical < 0) ? -1 : 1;
}

static	void	vertical_intercept(t_window *win_infos, t_ray *ray)
{
	double	next_vertical_touch_x;
	double	next_vertical_touch_y;

	vertical_values(win_infos, ray);
	next_vertical_touch_x = ray->x_intercept_vertical;
	next_vertical_touch_y = ray->y_intercept_vertical;
	while (next_vertical_touch_x >= 0 && next_vertical_touch_x <=
			win_infos->width && next_vertical_touch_y >= 0 &&
			next_vertical_touch_y <= win_infos->height)
	{
		if (has_wall_at(win_infos, next_vertical_touch_x -
				(ray->facing_left ? 1 : 0) + (ray->facing_right ? 1 : 0),
				next_vertical_touch_y))
		{
			ray->vertical_wall_hit = 1;
			ray->vertical_distance = distance(win_infos,
				next_vertical_touch_x, next_vertical_touch_y);
			break ;
		}
		else
		{
			next_vertical_touch_x += ray->x_step_vertical;
			next_vertical_touch_y += ray->y_step_vertical;
		}
	}
}

double			cast_ray(t_window *win_infos, t_ray *ray, int idx)
{
	double	horizontal_distance;
	double	vertical_distance;
	double	distance;

	horizontal_intercept(win_infos, ray);
	vertical_intercept(win_infos, ray);
	horizontal_distance = ray->horizontal_wall_hit ?
		ray->horizontal_distance : HUGE_VAL;
	vertical_distance = ray->vertical_wall_hit ?
		ray->vertical_distance : HUGE_VAL;
	if (horizontal_distance < vertical_distance)
	{
		distance = horizontal_distance;
		win_infos->intercept[idx] = 0;
		win_infos->wall_d[idx] = win_infos->player->x +
			distance * cos(ray->rotation_angle);
	}
	else
	{
		distance = vertical_distance;
		win_infos->intercept[idx] = 1;
		win_infos->wall_d[idx] = win_infos->player->y +
			distance * sin(ray->rotation_angle);
	}
	return (distance);
}

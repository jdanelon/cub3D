/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:53:52 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/26 11:32:20 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int				has_wall_at(t_window *win_infos, double x, double y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	if (x < 0 || x > win_infos->width || y < 0 || y > win_infos->height)
		return (OK);
	map_grid_index_x = (int)floor(x / win_infos->tile_size_x);
	map_grid_index_y = (int)floor(y / win_infos->tile_size_y);
	if (win_infos->map->map[map_grid_index_y][map_grid_index_x] == '2')
		is_sprite(win_infos, map_grid_index_x, map_grid_index_y);
	if (win_infos->map->map[map_grid_index_y][map_grid_index_x] == '1')
		return (OK);
	return (ERROR);
}

static	void	update_player(t_window *win_infos)
{
	double	move_step_ns;
	double	move_step_lo;
	double	new_player_x;
	double	new_player_y;

	win_infos->player->rotation_angle += win_infos->player->turn_direction *
		win_infos->player->rotation_speed;
	win_infos->player->rotation_angle =
		normalize_angle(win_infos->player->rotation_angle);
	move_step_ns = win_infos->player->walk_direction *
		win_infos->player->move_speed;
	move_step_lo = win_infos->player->move_sideways *
		win_infos->player->move_speed;
	new_player_x = win_infos->player->x +
		cos(win_infos->player->rotation_angle) * move_step_ns +
		sin(win_infos->player->rotation_angle) * move_step_lo;
	new_player_y = win_infos->player->y +
		sin(win_infos->player->rotation_angle) * move_step_ns -
		cos(win_infos->player->rotation_angle) * move_step_lo;
	if (!has_wall_at(win_infos, new_player_x, new_player_y))
	{
		win_infos->player->x = new_player_x;
		win_infos->player->y = new_player_y;
	}
}

static	t_ray	*init_ray(double ray_angle)
{
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	ray->rotation_angle = normalize_angle(ray_angle);
	ray->horizontal_wall_hit = 0;
	ray->vertical_wall_hit = 0;
	ray->horizontal_distance = 0;
	ray->vertical_distance = 0;
	ray->facing_down = (ray->rotation_angle > 0 &&
		ray->rotation_angle < PI) ? 1 : 0;
	ray->facing_up = !ray->facing_down;
	ray->facing_right = (ray->rotation_angle < (PI / 2) ||
		ray->rotation_angle > (3 * PI / 2)) ? 1 : 0;
	ray->facing_left = !ray->facing_right;
	return (ray);
}

static	void	cast_all_rays(t_window *win_infos)
{
	int		i;
	t_ray	**rays;
	double	ray_angle;

	i = 0;
	rays = (t_ray **)malloc(win_infos->width * sizeof(t_ray));
	ray_angle = win_infos->player->rotation_angle - (win_infos->fov_angle / 2);
	while (i < win_infos->width)
	{
		rays[i] = init_ray(ray_angle);
		win_infos->ray_distances[i] = cast_ray(win_infos, rays[i], i);
		win_infos->ray_angles[i] = ray_angle;
		free(rays[i]);
		ray_angle += win_infos->fov_angle / win_infos->width;
		i++;
	}
	free(rays);
}

int				raycasting(t_window *win_infos)
{
	int		i;
	double	ray_distance;
	double	distance_projection_plane;
	double	wall_strip_height;

	i = 0;
	update_player(win_infos);
	cast_all_rays(win_infos);
	distance_projection_plane = (win_infos->width / 2) /
		tan(win_infos->fov_angle / 2);
	while (i < win_infos->width)
	{
		ray_distance = win_infos->ray_distances[i];
		ray_distance *= cos(win_infos->ray_angles[i] -
			win_infos->player->rotation_angle);
		wall_strip_height = (win_infos->tile_size_y / ray_distance) *
			distance_projection_plane;
		if (wall_strip_height > win_infos->height)
			wall_strip_height = (double)win_infos->height;
		texturization(win_infos, i, ray_distance, wall_strip_height);
		put_ceiling_floor(win_infos, wall_strip_height, i);
		i++;
	}
	return (OK);
}

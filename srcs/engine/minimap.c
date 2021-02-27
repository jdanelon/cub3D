/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:53:36 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/26 11:32:11 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	void	render_minimap_grid(t_window *win_infos)
{
	int				i;
	int				j;
	unsigned int	color;

	j = 0;
	while (j < win_infos->map->height)
	{
		i = 0;
		while (i < win_infos->map->width[j])
		{
			if (win_infos->map->map[j][i] == '1')
				color = 0x80FFFFFF;
			else if (win_infos->map->map[j][i] == '2')
				color = 0x8000FF00;
			else
				color = 0;
			rect_minimap(win_infos, color, i, j);
			i++;
		}
		j++;
	}
}

static	void	render_minimap_ray(t_window *win_infos, double ray_angle,
									int column_id)
{
	line_ray(win_infos, ray_angle, (win_infos->ray_distances[column_id]) *
		win_infos->minimap_scale_factor);
}

static	void	render_minimap_player(t_window *win_infos, double x, double y)
{
	int	i;
	int	j;
	int	radius;

	radius = 5;
	j = y - radius;
	while (j <= y + radius)
	{
		i = x - radius;
		while (i <= x + radius)
		{
			if (sqrt(pow(i - x, 2.0) + pow(j - y, 2.0)) <= radius)
				pixel_put_to_img(win_infos->img, 0XFF0000,
									i * win_infos->minimap_scale_factor,
									j * win_infos->minimap_scale_factor);
			i++;
		}
		j++;
	}
}

int				minimap(t_window *win_infos)
{
	int		i;
	double	ray_angle;

	i = 0;
	render_minimap_grid(win_infos);
	while (i < win_infos->width)
	{
		render_minimap_ray(win_infos, win_infos->ray_angles[i], i);
		i++;
	}
	render_minimap_player(win_infos, win_infos->player->x,
		win_infos->player->y);
	return (OK);
}

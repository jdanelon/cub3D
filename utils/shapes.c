/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:51:57 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/26 11:36:30 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			rect_minimap(t_window *win_infos, int color, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	while (j < win_infos->tile_size_y * win_infos->minimap_scale_factor)
	{
		i = 0;
		while (i < win_infos->tile_size_x * win_infos->minimap_scale_factor)
		{
			pixel_put_to_img(win_infos->img, color,
								x * win_infos->tile_size_x *
									win_infos->minimap_scale_factor + i,
								y * win_infos->tile_size_y *
									win_infos->minimap_scale_factor + j);
			i++;
		}
		j++;
	}
}

static	void	line_update(t_geom_line *line, int *x0, int *y0)
{
	line->e2 = 2 * line->err;
	if (line->e2 >= line->dy)
	{
		line->err += line->dy;
		*x0 += line->sx;
	}
	if (line->e2 <= line->dx)
	{
		line->err += line->dx;
		*y0 += line->sy;
	}
}

void			line_ray(t_window *win_infos, double ray_angle, int len)
{
	int			x0;
	int			y0;
	t_geom_line	*line;

	x0 = (int)(win_infos->player->x * win_infos->minimap_scale_factor);
	y0 = (int)(win_infos->player->y * win_infos->minimap_scale_factor);
	line = (t_geom_line *)malloc(sizeof(t_geom_line));
	line->x1 = (int)(x0 + cos(ray_angle) * (len - 1));
	line->y1 = (int)(y0 + sin(ray_angle) * (len - 1));
	line->dx = abs((int)(line->x1 - x0));
	line->dy = -abs((int)(line->y1 - y0));
	line->sx = (x0 < line->x1) ? 1 : -1;
	line->sy = (y0 < line->y1) ? 1 : -1;
	line->err = line->dx + line->dy;
	while (1)
	{
		pixel_put_to_img(win_infos->img, 0xFF, x0, y0);
		if ((x0 == line->x1) && (y0 == line->y1))
			break ;
		line_update(line, &x0, &y0);
	}
	free(line);
}

void			rect(t_window *win_infos, int x, int y, int len_y)
{
	int	j;

	j = 0;
	while (j < len_y)
	{
		pixel_put_to_img(win_infos->img, 0XFFFFFF, x, y - j);
		j++;
	}
}

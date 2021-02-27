/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:05:10 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/27 22:43:47 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	void	calculate_values(t_window *win_infos, t_draw_sprite *ds)
{
	double	distance_projection_plane;

	distance_projection_plane = (win_infos->width / 2) /
		tan(win_infos->fov_angle / 2);
	ds->sprite_screen_x = (int)(win_infos->width / 2 -
		get_relative_distance(win_infos, ds));
	ds->sprite_height = (win_infos->tile_size_y / ds->distance) *
		distance_projection_plane;
	ds->draw_start_y = (win_infos->height - ds->sprite_height) / 2;
	if (ds->draw_start_y < 0)
		ds->draw_start_y = 0;
	ds->draw_end_y = (win_infos->height + ds->sprite_height) / 2;
	if (ds->draw_end_y >= win_infos->height)
		ds->draw_end_y = win_infos->height - 1;
	ds->sprite_width = (win_infos->sprite->width * ds->sprite_height) /
		win_infos->sprite->height;
	ds->draw_start_x = ds->sprite_screen_x - (ds->sprite_width / 2);
	if (ds->draw_start_x < 0)
		ds->draw_start_x = 0;
	ds->draw_end_x = ds->sprite_screen_x + (ds->sprite_width / 2);
	if (ds->draw_end_x >= win_infos->width)
		ds->draw_end_x = win_infos->width - 1;
	ds->stripe = ds->draw_start_x;
}

static	void	pix_on_sprite_image(t_window *win_infos, t_draw_sprite *ds)
{
	ds->tex_y = (ds->y - (int)(win_infos->height - ds->sprite_height) / 2) *
		win_infos->sprite->height / ds->sprite_height;
	ds->totcolor = win_infos->sprite->data[ds->tex_y *
		win_infos->sprite->size_line + ds->tex_x *
		(win_infos->sprite->bpp / 8)] + win_infos->sprite->data[ds->tex_y *
		win_infos->sprite->size_line + ds->tex_x *
		(win_infos->sprite->bpp / 8) + 1] + win_infos->sprite->data[ds->tex_y *
		win_infos->sprite->size_line + ds->tex_x *
		(win_infos->sprite->bpp / 8) + 2];
}

static	void	no_black(t_window *win_infos, t_draw_sprite *ds)
{
	win_infos->img->data[ds->y * win_infos->img->size_line +
		ds->stripe * (win_infos->img->bpp / 8)] =
		win_infos->sprite->data[ds->tex_y * win_infos->sprite->size_line +
		ds->tex_x * (win_infos->img->bpp / 8)];
	win_infos->img->data[ds->y * win_infos->img->size_line +
		ds->stripe * (win_infos->img->bpp / 8) + 1] =
		win_infos->sprite->data[ds->tex_y * win_infos->sprite->size_line +
		ds->tex_x * (win_infos->img->bpp / 8) + 1];
	win_infos->img->data[ds->y * win_infos->img->size_line +
		ds->stripe * (win_infos->img->bpp / 8) + 2] =
		win_infos->sprite->data[ds->tex_y * win_infos->sprite->size_line +
		ds->tex_x * (win_infos->img->bpp / 8) + 2];
}

static	void	make_sprite(t_window *win_infos, t_draw_sprite *ds)
{
	ds->sprite_x = (ds->sprites[ds->i].x + 0.5) * win_infos->tile_size_x;
	ds->sprite_y = (ds->sprites[ds->i].y + 0.5) * win_infos->tile_size_y;
	ds->distance = distance(win_infos, ds->sprite_x, ds->sprite_y);
	calculate_values(win_infos, ds);
	while (ds->stripe < ds->draw_end_x)
	{
		ds->tex_x = (int)((ds->stripe + (ds->sprite_width / 2 -
			ds->sprite_screen_x)) * win_infos->sprite->width /
			ds->sprite_width);
		if (sprite_on_fov(win_infos, ds) &&
			ds->distance < win_infos->ray_distances[ds->stripe])
		{
			ds->y = ds->draw_start_y;
			while (ds->y < ds->draw_end_y)
			{
				pix_on_sprite_image(win_infos, ds);
				if (ds->totcolor)
					no_black(win_infos, ds);
				ds->y++;
			}
		}
		ds->stripe++;
	}
}

int				draw_sprite(t_window *win_infos)
{
	t_draw_sprite	*ds;

	if (!(ds = (t_draw_sprite *)malloc(sizeof(t_draw_sprite))))
		return (ERROR);
	ft_bzero(ds, sizeof(t_draw_sprite));
	ds->i = 0;
	ds->sprites = list_to_tab(win_infos);
	sort_sprite(win_infos, ds->sprites,
		ft_lstsize((t_list *)win_infos->sprites_on_screen));
	while (ds->i < ft_lstsize((t_list *)win_infos->sprites_on_screen))
	{
		make_sprite(win_infos, ds);
		ds->i++;
	}
	free(ds->sprites);
	free(ds);
	return (OK);
}

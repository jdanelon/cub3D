/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:52:16 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/26 11:35:57 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	void	put_ceiling(t_window *win_infos, int i, int j)
{
	pixel_put_to_img(win_infos->img, win_infos->color_ceiling, i, j);
}

static	void	put_floor(t_window *win_infos, int i, int j)
{
	pixel_put_to_img(win_infos->img, win_infos->color_floor, i, j);
}

void			put_ceiling_floor(t_window *win_infos, double strip_height,
									int idx)
{
	int	draw_start;
	int	draw_end;

	draw_start = 0;
	draw_end = (win_infos->height - strip_height) / 2;
	while (draw_start < draw_end)
	{
		put_ceiling(win_infos, idx, draw_start);
		draw_start++;
	}
	draw_start = (win_infos->height + strip_height) / 2;
	draw_end = win_infos->height;
	while (draw_start < draw_end)
	{
		put_floor(win_infos, idx, draw_start);
		draw_start++;
	}
}

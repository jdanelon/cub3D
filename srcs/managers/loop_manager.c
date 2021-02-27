/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:54:29 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/30 14:39:54 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	void	clear_window(t_window *win_infos)
{
	int	x;
	int	y;

	y = 0;
	while (y < win_infos->height)
	{
		x = 0;
		while (x < win_infos->width)
		{
			pixel_put_to_img(win_infos->img, 0, x, y);
			x++;
		}
		y++;
	}
}

static	int		begin_game(t_window *win_infos)
{
	clear_window(win_infos);
	if (!raycasting(win_infos))
		leave(win_infos, "", 0);
	if (!draw_sprite(win_infos))
		return (ERROR);
	minimap(win_infos);
	free(win_infos->wall_d);
	free(win_infos->intercept);
	free(win_infos->ray_distances);
	free(win_infos->ray_angles);
	if (win_infos->save)
	{
		win_infos->save = 0;
		create_bmp(win_infos->img, "cub3D");
		leave(win_infos, "", 0);
	}
	mlx_put_image_to_window(win_infos->mlx_ptr, win_infos->win_ptr,
		win_infos->img->img_ptr, 0, 0);
}

int				loop_manager(void *param)
{
	int			i;
	double		ray_angle;
	t_window	*win_infos;

	win_infos = (t_window *)param;
	win_infos->ray_angles = (double *)malloc(win_infos->width * sizeof(double));
	win_infos->ray_distances = (double *)malloc(win_infos->width *
		sizeof(double));
	win_infos->intercept = (int *)malloc(win_infos->width * sizeof(int));
	win_infos->wall_d = (double *)malloc(win_infos->width * sizeof(double));
	if (!begin_game(win_infos))
		return (ERROR);
	return (OK);
}

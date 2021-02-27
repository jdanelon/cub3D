/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:54:58 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/30 14:37:29 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	void	free_map(t_window *win_infos, int errno)
{
	int	i;

	i = 0;
	free(win_infos->map->width);
	if (errno != -2)
	{
		while (i < win_infos->map->height)
			free(win_infos->map->map[i++]);
		free(win_infos->map->map);
	}
}

static	void	free_rest(t_window *win_infos, int errno)
{
	if (errno != -1)
	{
		if (win_infos->img->img_ptr)
			mlx_destroy_image(win_infos->mlx_ptr, win_infos->img->img_ptr);
		free(win_infos->img);
		if (win_infos->win_ptr)
			mlx_destroy_window(win_infos->mlx_ptr, win_infos->win_ptr);
	}
}

void			free_all(t_window *win_infos, int errno)
{
	int	i;

	i = 0;
	free(win_infos->player);
	free_map(win_infos, errno);
	free(win_infos->map);
	while (i < 4)
	{
		if (win_infos->textures[i]->img_ptr)
		{
			mlx_destroy_image(win_infos->mlx_ptr,
				win_infos->textures[i]->img_ptr);
		}
		free(win_infos->textures[i++]);
	}
	free(win_infos->textures);
	if (win_infos->sprite->img_ptr)
		mlx_destroy_image(win_infos->mlx_ptr, win_infos->sprite->img_ptr);
	free(win_infos->sprite);
	free(win_infos->sprites_on_screen);
	if (!errno)
		free_rest(win_infos, errno);
	free(win_infos->mlx_ptr);
	free(win_infos);
}

int				event_destroy_window(void *param)
{
	t_window	*win_infos;

	win_infos = (t_window *)param;
	leave(win_infos, "", 0);
	return (OK);
}

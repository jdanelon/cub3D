/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:55:34 by jdanelon          #+#    #+#             */
/*   Updated: 2021/02/23 14:34:04 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static	t_window	*init_game_window_one(void)
{
	t_window	*new_win_infos;

	new_win_infos = (t_window *)malloc(sizeof(t_window));
	ft_bzero(new_win_infos, sizeof(t_window));
	if (!(new_win_infos->mlx_ptr = mlx_init()))
		return (ERROR);
	new_win_infos->map_description_found = 0;
	new_win_infos->space_after_map_description_found = 0;
	new_win_infos->width = -20;
	new_win_infos->height = -20;
	new_win_infos->color_floor = -20;
	new_win_infos->color_ceiling = -20;
	new_win_infos->fov_angle = 60 * (PI / 180);
	new_win_infos->minimap_scale_factor = 0.25;
	return (new_win_infos);
}

static	int			init_game_window_two(t_window *win_infos)
{
	int		i;
	char	*map_string;

	i = 0;
	win_infos->save = 0;
	if (!(map_string = treat_description(win_infos, win_infos->map->map_name)))
		return (ERROR);
	if (win_infos->width == -20 && win_infos->height == -20)
		leave(win_infos, "Error\nResolution was not set", -1);
	if (win_infos->color_floor == -20 || win_infos->color_ceiling == -20)
		leave(win_infos, "Error\nFloor/ceiling color was not set", -1);
	while (i < 4)
	{
		if (!win_infos->textures[i]->img_ptr)
			leave(win_infos, "Error\nOne path texture was not set", -1);
		i++;
	}
	if (!win_infos->sprite->img_ptr)
		leave(win_infos, "Error\nSprite was not set", -1);
	win_infos->map->map = map_from_string(win_infos, map_string);
	if (!(win_infos->win_ptr = mlx_new_window(win_infos->mlx_ptr,
			win_infos->width, win_infos->height, "cub3D")))
		return (ERROR);
	win_infos->img = new_image(win_infos, win_infos->width, win_infos->height);
	return (OK);
}

void				leave(t_window *win_infos, char *msg, int errno)
{
	free_all(win_infos, errno);
	ft_putstr_fd(msg, 1);
	if (msg[0])
		ft_putchar_fd('\n', 1);
	exit(errno);
}

static	void		need_save(t_window *win_infos, char **argv)
{
	if (argv[2] && ft_strlen(argv[2]) > 0)
	{
		if (ft_strlen(argv[2]) == ft_strlen("--save") &&
				ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
		{
			win_infos->save = 1;
			loop_manager(win_infos);
		}
		else
			putstr_info_cmd();
	}
	else
		win_infos->save = 0;
}

int					main(int argc, char **argv)
{
	int			fd;
	t_window	*win_infos;

	if (argc < 2 || argc > 3)
		putstr_info_cmd();
	win_infos = init_game_window_one();
	if (!init_game_player(win_infos) ||
			!init_game_sprite(win_infos) ||
			!init_game_textures(win_infos, 4) ||
			!init_game_map(win_infos, argv[1]) ||
			!init_game_window_two(win_infos))
		leave(win_infos, "Error\nAt initializing game", -1);
	need_save(win_infos, argv);
	mlx_hook(win_infos->win_ptr, 2, 1L << 0, event_key_pressed, win_infos);
	mlx_hook(win_infos->win_ptr, 3, 1L << 1, event_key_released, win_infos);
	mlx_hook(win_infos->win_ptr, 33, 1L << 17, event_destroy_window, win_infos);
	mlx_loop_hook(win_infos->mlx_ptr, loop_manager, win_infos);
	if (win_infos->save != 1)
		mlx_loop(win_infos->mlx_ptr);
	leave(win_infos, "", 0);
	return (0);
}

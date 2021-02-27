/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_info_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:51:50 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/30 15:25:53 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	putstr_info_cmd(void)
{
	ft_putstr_fd("Cub3D usage: \n", 1);
	ft_putstr_fd("\n./Cub3D <\"name\".cub>", 1);
	ft_putstr_fd("\n./Cub3D <\"name\".cub> <--save>\n", 1);
	exit(-1);
}

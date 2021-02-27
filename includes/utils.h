/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:50:28 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/01 15:50:29 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <fcntl.h>

int		ft_is_whitespace(int c);
int		get_next_line(int fd, char **line);
void	putstr_info_cmd(void);

#endif

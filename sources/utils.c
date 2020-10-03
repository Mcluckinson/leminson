/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 21:16:14 by cyuriko           #+#    #+#             */
/*   Updated: 2020/02/09 15:34:30 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_step(int ant_num, char *room_name, t_main *main)
{
	ft_putchar('L');
	ft_putnbr((main->original_ants + 1 - ant_num));
	ft_putchar('-');
	ft_putstr(room_name);
	ft_putchar(' ');
}

int			ft_error(const char *error)
{
	ft_putendl_fd(error, 2);
	exit(-1);
}

int			del_line_and_return(char *line, int ret)
{
	if (ret || line)
		free(line);
	line = NULL;
	return (ret);
}

int			is_all_digits(char *line)
{
	int		i;

	i = -1;
	if (!line)
		return (0);
	while (line[++i])
	{
		if (line[i] >= '0' && line[i] <= '9')
			continue;
		else
			return (0);
	}
	return (1);
}

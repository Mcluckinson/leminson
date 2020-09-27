/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 21:04:35 by cyuriko           #+#    #+#             */
/*   Updated: 2020/03/15 21:26:20 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int			is_ants(char *line)
{
	if (is_all_digits(line))
		return (ft_atoi(line));
	return (0);
}

int				read_ants(t_main *data)
{
	char		*line;
	int			ants;
	int         success;

	ants = 0;
	while ((success = get_next_line(data->del_me_fd, &line)))
	{
		if (success < 1)
			ft_error("u tryna segv me?? D:<");
		if (line)
		{
			if (is_comment(line))
			{
				if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
					return (del_line_and_return(line, 0));
				free(line);
				continue;
			}

			else
			{
				ants = is_ants(line);
				if (!ants)
					return (del_line_and_return(line, 0));
				data->ants = ants;
				break;
			}
		}
	}
	if (!check_ants_quantity(ants, line))
		return (del_line_and_return(line, 0));
	return (del_line_and_return(line, success));
}

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

static void			segv_checker(int success, char *line)
{
	if (success < 1 || !line)
		ft_error("u tryna segv me?? D:<");
}

int					read_ants(t_main *data)
{
	char		*line;
	int			success;

	while ((success = get_next_line(data->del_me_fd, &line)))
	{
		segv_checker(success, line);
		if (is_comment(line))
		{
			if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
				return (del_line_and_return(line, 0));
			print_and_delete(line);
			continue;
		}
		data->ants = is_ants(line);
		if (!data->ants)
			return (del_line_and_return(line, 0));
		ft_putendl_fd(line, 1);
		break ;
	}
	if (!success)
		return (0);
	return (check_ants_quantity(data->ants, line) ? del_line_and_return(line, 1)
	: del_line_and_return(line, 0));
}

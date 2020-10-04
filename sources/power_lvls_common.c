/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power_lvls_common.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 14:27:19 by cyuriko           #+#    #+#             */
/*   Updated: 2020/10/04 14:27:22 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

bool		set_start_end(t_room *start, t_room *end)
{
	if (!start || !end)
		return (false);
	start->level = START;
	end->level = END;
	return (true);
}

int			set_lvl_one(t_room *start, t_link *links)
{
	t_link	*counter;
	int		links_done;

	links_done = 0;
	counter = links;
	while (counter)
	{
		if (counter->first_room == start)
		{
			counter->second_room->level++;
			links_done++;
		}
		if (counter->second_room == start)
		{
			links_done++;
			counter->first_room->level++;
		}
		counter = counter->next;
	}
	return (links_done);
}

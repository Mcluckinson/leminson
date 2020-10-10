/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_worse_kidz.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:58:00 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:58:02 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static bool	check_first_room(t_link *link, t_main *map)
{
	if (link->first_room == map->start)
	{
		if (!link->second_room->outputs)
			return (false);
		return (true);
	}
	if (!link->first_room->inputs || !link->first_room->outputs)
		return (false);
	return (true);
}

static bool	check_second_room(t_link *link, t_main *map)
{
	if (link->second_room == map->end)
	{
		if (!link->first_room->inputs)
			return (false);
		return (true);
	}
	if (!link->second_room->inputs || !link->second_room->outputs)
		return (false);
	return (true);
}

void		delete_worse_kids(t_main *map)
{
	t_link	*counter;
	t_link	*buff_counter;
	int		linkz_start;
	int		linkz_destroyed_iteration;

	linkz_start = count_links(map->all_links_here);
	linkz_destroyed_iteration = 0;
	while (linkz_start != linkz_destroyed_iteration)
	{
		linkz_start = count_links(map->all_links_here);
		counter = map->all_links_here;
		while (counter)
		{
			buff_counter = counter->next;
			if (!check_first_room(counter, map) ||
			!check_second_room(counter, map))
				delete_link(counter, map);
			counter = buff_counter;
		}
		linkz_destroyed_iteration = count_links(map->all_links_here);
	}
}

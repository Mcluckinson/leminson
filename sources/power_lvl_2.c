/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power_lvl_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:59:37 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:59:38 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static bool		check_first(t_link *counter, t_main *map)
{
	if (counter->first_room->level
	&& (!counter->second_room->level
	|| counter->second_room->level > counter->first_room->level + 1)
	&& counter->first_room != map->end && counter->first_room != map->start
	&& counter->second_room != map->start && counter->second_room != map->end)
		return (true);
	return (false);
}

static bool		check_second(t_link *counter, t_main *map)
{
	if (counter->second_room->level
	&& (!counter->first_room->level
	|| counter->first_room->level > counter->second_room->level + 1)
	&& counter->second_room != map->end && counter->second_room != map->start
	&& counter->first_room != map->start && counter->first_room != map->end)
		return (true);
	return (false);
}

static int		set_other_lvls(t_link *links, t_main *map)
{
	int		links_done;
	t_link	*counter;

	counter = links;
	links_done = 0;
	while (counter)
	{
		if (check_first(counter, map))
		{
			counter->second_room->level = counter->first_room->level + 1;
			map->max_lvl = map->max_lvl < counter->second_room->level ?
					counter->second_room->level : map->max_lvl;
			links_done++;
		}
		if (check_second(counter, map))
		{
			counter->first_room->level = counter->second_room->level + 1;
			map->max_lvl = map->max_lvl < counter->first_room->level ?
					counter->first_room->level : map->max_lvl;
			links_done++;
		}
		counter = counter->next;
	}
	return (links_done);
}

static int		set_bad_links(t_link *links, t_main *map)
{
	t_link	*counter;
	int		lvls_done;

	counter = links;
	lvls_done = 0;
	while (counter)
	{
		if (!counter->first_room->level && counter->first_room != map->start)
		{
			counter->first_room->level = -1;
			lvls_done++;
		}
		if (!counter->second_room->level && counter->second_room != map->start)
		{
			counter->second_room->level = -1;
			lvls_done++;
		}
		counter = counter->next;
	}
	return (0);
}

int				power_levels(t_main *map)
{
	int lvls_done_on_iteration;

	lvls_done_on_iteration = 0;
	if (!set_start_end(map->start, map->end))
		ft_error("INVALID MAP KEK");
	lvls_done_on_iteration += set_lvl_one(map->start, map->all_links_here);
	if (lvls_done_on_iteration == 0)
		ft_error("INVALID MAP KEK");
	else
		map->max_lvl = 1;
	while (1)
	{
		lvls_done_on_iteration = set_other_lvls(map->all_links_here, map);
		if (!lvls_done_on_iteration)
			break ;
	}
	while (1)
	{
		lvls_done_on_iteration = set_bad_links(map->all_links_here, map);
		if (!lvls_done_on_iteration)
			break ;
	}
	return (0);
}

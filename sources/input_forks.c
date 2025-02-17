/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:58:51 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:58:54 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static bool		check_if_good(t_link *challenger, t_link *all_links)
{
	t_link *counter;
	t_link *to_check;

	counter = all_links;
	to_check = challenger;
	if (!to_check->first_room->level)
		return (true);
	while (counter)
	{
		counter = all_links;
		while (counter && counter->second_room != to_check->first_room)
			counter = counter->next;
		if (!counter)
			return (false);
		if (!counter->first_room->level)
			return (true);
		if (counter->first_room->outputs > 1)
			return (false);
		to_check = counter;
	}
	return (false);
}

static bool		check_if_better(t_link *old_good,
t_link *challenger, t_link *all_links)
{
	if (!old_good || old_good == challenger)
		return (true);
	if (old_good->first_room->outputs == 1
	&& challenger->first_room->outputs > 1)
		return (false);
	if (old_good->first_room->outputs > 1
	&& challenger->first_room->outputs == 1)
		return (true);
	if (old_good->first_room->outputs == 1
	&& challenger->first_room->outputs == 1)
	{
		if (check_if_good(challenger, all_links))
			return (true);
		return (false);
	}
	return (false);
}

static t_link	*find_good(t_room *room, t_link *links)
{
	t_link *best;
	t_link *final;

	final = NULL;
	best = links;
	while (best)
	{
		if (best->second_room == room)
		{
			if (!final)
				final = best;
			if (check_if_better(final, best, links))
				final = best;
		}
		best = best->next;
	}
	return (final);
}

static void		delete_others(t_room *room, t_link *links,
t_link *best, t_main *map)
{
	t_link *to_delete;
	t_link *to_delete_buff;

	to_delete = links;
	while (to_delete)
	{
		to_delete_buff = to_delete->next;
		if (to_delete->second_room == room)
		{
			if (to_delete == best)
			{
				to_delete = to_delete_buff;
				continue;
			}
			else
				delete_link(to_delete, map);
			to_delete = to_delete_buff;
			continue;
		}
		to_delete = to_delete_buff;
	}
}

void			delete_input(t_room *room, t_main *map)
{
	t_link *link_to_save;

	if (should_delete(room, map))
	{
		link_to_save = find_good(room, map->all_links_here);
		delete_others(room, map->all_links_here, link_to_save, map);
	}
	delete_worse_kids(map);
}

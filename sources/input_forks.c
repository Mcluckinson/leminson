//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"

static bool should_delete(t_room *room, t_main *map)
{
	if (room == map->start || room == map->end)
		return (false);
	if (room->inputs < 2)
		return (false);
//	if (room->level == 1)
//		return (false);
	return (true);
}

static bool is_good(t_link *link)
{
	return (link->first_room->outputs == 1 ? true : false);
}

static bool check_if_good(t_link *challenger, t_link *all_links)
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
		if (counter->first_room->outputs > 1)///WAIT WHAT
			return (false);
		to_check = counter;
	}
}

static bool check_if_better(t_link *old_good, t_link *challenger, t_link *all_links)
{
	/*
	 * will return true if challenger is better than old good, will return false if not
	 * maybe we should check paths len as well, try it if it works but not well enough
	 */
	if (!old_good || old_good == challenger)
		return (true);
	if (old_good->first_room->outputs == 1 && challenger->first_room->outputs > 1)
		return (false);
	if (old_good->first_room->outputs > 1 && challenger->first_room->outputs == 1)
		return (true);
	if (old_good->first_room->outputs == 1 && challenger->first_room->outputs == 1)
	{
		if (check_if_good(challenger, all_links))
			return (true);
		return (false);
	}
	return (false);
}

static t_link *find_good(t_room *room, t_link *links)
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

static void delete_others(t_room *room, t_link *links, t_link *best, t_main *map)
{
	t_link *to_delete;

	to_delete = links;
	while (to_delete)
	{
		if (to_delete->second_room == room)
		{
			if (to_delete == best)
			{
				to_delete = to_delete->next;
				continue;
			}
			else
			{
				//to_delete->second_room->inputs--;
				//to_delete->first_room->outputs--;
				delete_link(to_delete, map);
				printf("DELETED INPUT\n");
			}
			to_delete = to_delete->next;/////is it a segv?
			continue;
		}
		to_delete = to_delete->next;
	}
}

void delete_input(t_room *room, t_main *map)
 {
	t_link *link_to_save;

	if (should_delete(room, map))
	{
		link_to_save = find_good(room, map->all_links_here);
		delete_others(room, map->all_links_here, link_to_save, map);
	}
	delete_worse_kids(map->all_links_here, map);//////maybe all it needs is map?
	int linkz = count_WLINKZ_delete_me(map->all_links_here);
 }
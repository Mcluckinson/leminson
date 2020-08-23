//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"

static bool should_delete(t_room *room, t_main *map)
{
	if (room == map->start)
		return (false);
	if (room->inputs < 2)
		return (false);
	if (room->level == 1)
		return (false);
	return (true);
}

static t_link *find_good(t_room *room, t_link *links)
{
	t_link *best;
	t_link *first;

	first = NULL;
	best = links;
	while (best)
	{
		if (best->second_room == room)
		{
			first = best;
			if (best->first_room->outputs == 1)
				return (best);
		}
		best = best->next;
	}
	return (first);
}

static void delete_others(t_room *room, t_link *links, t_link *best)
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
				to_delete->second_room->inputs--;
				to_delete->first_room->outputs--;
				delete_link(to_delete);
			}
			to_delete = to_delete->next;
			continue;
		}
	}
}

void delete_input(t_room *room, t_main *map)
 {
	t_link *link_to_save;

	link_to_save = map->all_links_here;
	if (should_delete(room, map))
	{
		link_to_save = find_good(room, map->all_links_here);
		delete_others(room, map->all_links_here, link_to_save);
	}
	delete_worse_kids(map->all_links_here);
 }
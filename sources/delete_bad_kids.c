//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"
/*
 * this will delete links containing rooms with bad lvl and links between same-lvl rooms
 */
static bool	check_link(t_link *link)
{
	if (link)
	{
		if (link->first_room->level == -1 || link->second_room->level == -1 ||
		link->first_room->level == link->second_room->level)
			return (false);
	}
	return (true);
}

void	delete_link(t_link *link, t_main *map)
{
	t_link *to_delete;

	to_delete = link;
	if (link->next)
	{
		if (link->prev)
			link->next->prev = link->prev;
		else
			link->next->prev = NULL;
	}
	if (link->prev)
	{
		if (link->next)
			link->prev->next = link->next;
		else
			link->prev->next = NULL;
	}
	if (to_delete == map->all_links_here)
		map->all_links_here = map->all_links_here->next;
	if (to_delete->first_room->outputs)///needed!
		to_delete->first_room->outputs--;
	if (to_delete->second_room->inputs)///needed!
		to_delete->second_room->inputs--;
	free(to_delete);
	to_delete = NULL;
}

void 		delete_bad_kids(t_link *links, t_main *map)
{
	t_link *counter;

	counter = links;
	while (counter)
	{
		if (!check_link(counter))
			delete_link(counter, map);
		counter = counter->next;
	}
}
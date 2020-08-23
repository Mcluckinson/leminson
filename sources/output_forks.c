//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"

static bool should_delete_output(t_room *room, t_main *map)
{
	if (room == map->end || room == map->start)
		return (false);
	if (room->outputs < 2)
		return (false);
	return (true);
}

static t_link *find_good_output(t_room *room, t_main *map)
{
/*	t_link *best;
	t_link *counter;
	int path_len;

	path_len
	counter = map->all_links_here;
	while (counter)
	{
		if (counter->first_room == room)
		{

		}
	}*/
	return (NULL);
}

static void delete_other_outputs(t_room *room, t_link *links)
{
	return ;
}

void delete_output(t_room *room, t_main *map)
{
	t_link *link_to_save;

	link_to_save = map->all_links_here;
	if (should_delete_output(room, map))
	{
		link_to_save = find_good_output(room, map->all_links_here);
		delete_other_outputs(room, map->all_links_here);
	}
	delete_worse_kids(map->all_links_here);
}
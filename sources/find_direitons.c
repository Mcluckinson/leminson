//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"
//////rename file
/*
 * this will change rooms links so first room lvl is always < second room lvl
 */
static void fix_link(t_link *link)
{
	if (link->first_room->level > link->second_room->level)
	{
		link->first_room+= link->second_room->level;
		link->second_room->level = link->first_room->level
				- link->second_room->level;
		link->first_room->level-= link->second_room->level;
	}
}

void directions(t_link *links)
{
	t_link *counter;

	counter = links;
	while (counter)
	{
		fix_link(counter);
		counter = counter->next;
	}
}
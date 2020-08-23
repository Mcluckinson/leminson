//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"

/*
 * this will delete dead ends
 */

static bool check_first_room(t_link *link)
{
	if (link->first_room->level == START)
	{
		if (!link->second_room->outputs)
			return (false);
		return (true);
	}
	if (!link->first_room->inputs || !link->first_room->outputs)
		return (false);
	return (true);
}

static bool check_second_room(t_link *link)
{
	if (link->second_room->level == END)
	{
		if (!link->first_room->inputs)
			return (false);
		return (true);
	}
	if (!link->second_room->inputs || link->second_room->outputs)
		return (false);
	return (true);
}

void 	delete_worse_kids(t_link *links)
{
	t_link *counter;

	counter = links;
	while (counter)
	{
		if (!check_first_room(counter) || !check_second_room(counter))
			delete_link(counter);
		counter = counter->next;
	}
}